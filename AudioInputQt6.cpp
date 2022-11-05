#include "Audio.h"
#include "AudioInputQt6.h"
#include <QAudioDevice>
#include <QAudioInput>
#include <QAudioSource>
#include <QDebug>
#include <QIODevice>
#include <QMediaDevices>
#include <utility>

namespace {

// QueueWriter

class QueueWriter : public QIODevice {
public:
	std::deque<uint8_t> *queue_;
	qint64 readData(char *data, qint64 len) override
	{
		(void)data;
		(void)len;
		return 0;
	}
	qint64 writeData(const char *data, qint64 len) override
	{
		uint8_t const *begin = (uint8_t const *)data;
		uint8_t const *end = begin + len;
		queue_->insert(queue_->end(), begin, end);
		return len;
	}
	qint64 bytesAvailable() const override
	{
		return 0;
	}
	qint64 size() const override
	{
		return 0;
	}
};

// QueueReader

class QueueReader : public QIODevice {
public:
	std::deque<uint8_t> *queue_;
	qint64 readData(char *data, qint64 len) override;
	qint64 writeData(const char *data, qint64 len) override;
	qint64 bytesAvailable() const override;
	qint64 size() const override;
};

qint64 QueueReader::readData(char *data, qint64 len)
{
	qint64 n = std::min(len, (qint64)queue_->size());
	std::copy(queue_->begin(), queue_->begin() + n, data);
	queue_->erase(queue_->begin(), queue_->begin() + n);
	return n;
}

qint64 QueueReader::writeData(const char *data, qint64 len)
{
	(void)data;
	(void)len;
	return 0;
}

qint64 QueueReader::bytesAvailable() const
{
	return (int)queue_->size();
}

qint64 QueueReader::size() const
{
	return (int)queue_->size();
}

} // namespace

// AudioInput

struct AudioInput::Private {
	QAudioDevice device;
	std::shared_ptr<QAudioInput> input;
	std::shared_ptr<QAudioSource> source;
	std::deque<uint8_t> queue;
	QueueWriter writer;
	QueueReader reader;
};

AudioInput::AudioInput()
	: m(new Private)
{
}

AudioInput::~AudioInput()
{
	delete m;
}

QString AudioInput::description()
{
	return m->device.description();
}

void AudioInput::start(const AudioDevice &dev, const QAudioFormat &format)
{
	stop();
	m->device = dev.device_;
	m->input = std::make_shared<QAudioInput>(m->device);
	m->source = std::make_shared<QAudioSource>(m->device, format);
	m->writer.queue_ = &m->queue;
	m->reader.queue_ = &m->queue;
	m->writer.open(QueueWriter::WriteOnly);
	m->reader.open(QueueWriter::ReadOnly);
	m->source->start(&m->writer);
}

void AudioInput::stop()
{
	m->device = {};
	m->input.reset();
	m->source.reset();
	m->queue.clear();
	m->writer.close();
	m->reader.close();
}

int AudioInput::bytesAvailable() const
{
	return (int)m->reader.bytesAvailable();
}

int AudioInput::read(char *data, int maxlen)
{
	return (int)m->reader.read(data, maxlen);
}

QByteArray AudioInput::readAll()
{
	return m->reader.read(m->reader.bytesAvailable());
}
