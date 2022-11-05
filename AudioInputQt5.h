#ifndef AUDIOINPUTQT5_H
#define AUDIOINPUTQT5_H

#include "AudioAbstractIO.h"

class AudioInput : public AbstractAudioInput {
private:
	struct Private;
	Private *m;
public:
	AudioInput();
	~AudioInput() override;
	QString description() override;
	void start(const AudioDevice &dev, QAudioFormat const &format) override;
	void stop() override;
	int bytesAvailable() const override;
	int read(char *data, int maxlen) override;
	QByteArray readAll() override;

	// AbstractAudioInput interface
public:
};

#endif // AUDIOINPUTQT5_H
