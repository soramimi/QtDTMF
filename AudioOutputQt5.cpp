#include "AudioOutputQt5.h"
#include "Audio.h"
#include <QAudioFormat>
#include <QAudioOutput>
#include <memory>

// AudioOutput

struct AudioOutput::Private {
	QString description;
	std::shared_ptr<QAudioOutput> output;
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
	stop();
	RECOMMENDED_BUFFER_SIZE = format.bytesForFrames(1) * format.sampleRate() / 20;
	m->description = dev.device_.deviceName();
	m->output = std::make_shared<QAudioOutput>(format);
	m->output->setBufferSize(RECOMMENDED_BUFFER_SIZE);
    m->output->start(out);
}

void AudioOutput::stop()
{
	m->output.reset();
}

int AudioOutput::bytesFree(OutputBuffer *out) const
{
	(void)out;
	return m->output->bytesFree();
}



