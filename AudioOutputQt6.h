#ifndef AUDIOOUTPUTQT6_H
#define AUDIOOUTPUTQT6_H

#include "AudioAbstractIO.h"
#include <QIODevice>

class OutputBuffer;

class AudioOutput : public AbstractAudioOutput {
private:
	struct Private;
	Private *m;
public:
	AudioOutput();
	~AudioOutput() override;
	QString description() override;
	void start(AudioDevice const &dev, const QAudioFormat &format, QIODevice *out) override;
	void stop() override;
	int bytesFree(OutputBuffer *out) const;
};

#endif // AUDIOOUTPUTQT6_H
