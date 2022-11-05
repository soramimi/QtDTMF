#ifndef AUDIOOUTPUTQT5_H
#define AUDIOOUTPUTQT5_H

#include "AudioAbstractIO.h"

class OutputBuffer;

class OutputBuffer : public QIODevice {
protected:
	qint64 readData(char *data, qint64 maxlen) override
	{
		(void)data;
		(void)maxlen;
		return 0;
	}
	qint64 writeData(const char *data, qint64 len) override
	{
		(void)data;
		(void)len;
		return 0;
	}
public:
	std::deque<uint8_t> queue_;
	bool open(QIODevice::OpenMode mode) override
	{
		(void)mode;
		return true;
	}
	void close() override
	{
	}
};

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
	void write(const uint8_t *ptr, int len, OutputBuffer *outbuf);
};

#endif // AUDIOOUTPUTQT5_H
