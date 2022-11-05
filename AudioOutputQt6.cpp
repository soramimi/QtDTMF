#include "AudioOutputQt6.h"
#include "Audio.h"
#include <QAudioOutput>
#include <QAudioSink>
#include <QDebug>
#include <QMediaDevices>
#include <memory>

// AudioOutput

struct AudioOutput::Private {
	QAudioDevice device;
	std::shared_ptr<QAudioOutput> output;
	std::shared_ptr<QAudioSink> sink;
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
	return m->device.description();
}

void AudioOutput::start(AudioDevice const &dev, const QAudioFormat &format, QIODevice *out)
{
	stop();
	RECOMMENDED_BUFFER_SIZE = format.bytesForFrames(1) * format.sampleRate() / 20;
	m->device = dev.device_;
	m->output = std::make_shared<QAudioOutput>(m->device);
	m->sink = std::make_shared<QAudioSink>(m->device, format);
	m->sink->start(out);
}

void AudioOutput::stop()
{
	m->device = {};
	m->output.reset();
	m->sink.reset();
}

int AudioOutput::bytesFree(OutputBuffer *out) const
{
	int n = (int)out->queue_.size();
	if (n < RECOMMENDED_BUFFER_SIZE) {
		n = RECOMMENDED_BUFFER_SIZE - n;
		n = std::min(n, (int)m->sink->bytesFree());
		return n;
	}
	return 0;
}

void AudioOutput::write(uint8_t const *ptr, int len, OutputBuffer *out)
{
	out->write(ptr, len);
}


