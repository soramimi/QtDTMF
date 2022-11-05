#include "AudioOutputQt5.h"
#include "Audio.h"
#include <QAudioFormat>
#include <QAudioOutput>
#include <memory>

// AudioOutput

struct AudioOutput::Private {
	QString description;
	std::shared_ptr<QAudioOutput> output;
	QIODevice *device = nullptr;
};

AudioOutput::AudioOutput()
	: m(new Private)
{
}

AudioOutput::~AudioOutput()
{
	delete m;
}

QString AudioOutput::description()
{
	return m->description;
}


void AudioOutput::start(AudioDevice const &dev, QAudioFormat const &format, QIODevice *out)
{
	(void)out;
	stop();
	RECOMMENDED_BUFFER_SIZE = format.bytesForFrames(1) * format.sampleRate() / 20;
	m->description = dev.device_.deviceName();
	m->output = std::make_shared<QAudioOutput>(format);
	m->output->setBufferSize(RECOMMENDED_BUFFER_SIZE);
	m->device = m->output->start();
}

void AudioOutput::stop()
{
	m->output.reset();
	m->device = nullptr;
}

int AudioOutput::bytesFree(OutputBuffer *out) const
{
	(void)out;
	return m->output->bytesFree();
}

void AudioOutput::write(uint8_t const *ptr, int len, OutputBuffer *outbuf)
{
	outbuf->queue_.insert(outbuf->queue_.end(), ptr, ptr + len);

	std::vector<uint8_t> buf;
	int n = std::min((int)outbuf->queue_.size(), m->output->bytesFree());
	buf.insert(buf.end(), outbuf->queue_.begin(), outbuf->queue_.begin() + n);
	m->device->write((char const *)buf.data(), (int)buf.size());
	outbuf->queue_.erase(outbuf->queue_.begin(), outbuf->queue_.begin() + n);
}

