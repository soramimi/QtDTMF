#ifndef AUDIOOUTPUTQT5_H
#define AUDIOOUTPUTQT5_H

#include "AudioAbstractIO.h"

class OutputBuffer;


class AudioOutput : public AbstractAudioOutput {
private:
	struct Private;
	Private *m;
public:
	AudioOutput();
	~AudioOutput() override;
	QString description();
	void start(const AudioDevice &dev, const QAudioFormat &format, QIODevice *out) override;
	void stop() override;
	int bytesFree(OutputBuffer *out) const;
};

#endif // AUDIOOUTPUTQT5_H
