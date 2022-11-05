#include "Audio.h"
#include "AudioInputQt5.h"
#include <QAudioInput>
#include <memory>

// AudioInput

struct AudioInput::Private {
	QString description;
	std::shared_ptr<QAudioInput> input;
	QIODevice *reader = nullptr;
};

AudioInput::AudioInput()
	: m(new Private)
{
}

AudioInput::~AudioInput()
{
	stop();
	delete m;
}

QString AudioInput::description()
{
	return m->description;
}

void AudioInput::start(const AudioDevice &dev, QAudioFormat const &format)
{
	stop();
	m->description = dev.device_.deviceName();
	m->input = std::shared_ptr<QAudioInput>(new QAudioInput(format));
	m->reader = m->input->start();
}

void AudioInput::stop()
{
	m->reader = nullptr;
	m->input.reset();
}

int AudioInput::bytesAvailable() const
{
	return m->input->bytesReady();
}

int AudioInput::read(char *data, int maxlen)
{
	return m->reader->read(data, maxlen);
}

QByteArray AudioInput::readAll()
{
	QByteArray ba;
	if (m->reader) {
		ba = m->reader->readAll();
	}
	return ba;
}


