#ifndef AUDIOOUTPUTQT6_H
#define AUDIOOUTPUTQT6_H

#include "AudioAbstractIO.h"
#include <QIODevice>

class QIODevice;

class OutputBuffer : public QIODevice {
	friend class AudioOutput;
private:
	const int MINSAMPLES = 4;
	const int MINSIZE = int(sizeof(int16_t) * 2 * MINSAMPLES);
	std::deque<uint8_t> queue_;
	qint64 readData(char *data, qint64 len) override
	{
		int n = std::min((int)len, (int)queue_.size());
		n = std::min(n, MINSIZE);
		if (n > 0) {
			std::copy(queue_.begin(), queue_.begin() + (int)n, data);
			queue_.erase(queue_.begin(), queue_.begin() + (int)n);
		}
		if (queue_.empty()) {
			if (n & 1) {
				data[n] = 0;
				n++;
			}
			while (n < MINSIZE) {
				*(int16_t *)(data + n) = 0;
				n += sizeof(int16_t);
			}
		}
		return (qint64)n;
	}
	qint64 writeData(const char *data, qint64 len) override
	{
		(void)data;
		(void)len;
		return 0;
	}
	qint64 bytesAvailable() const override
	{
		return std::min(MINSIZE, (int)queue_.size());
	}
	qint64 size() const override
	{
		return std::min(MINSIZE, (int)queue_.size());
	}
	int write(uint8_t const *ptr, int len)
	{
		uint8_t const *begin = (uint8_t const *)ptr;
		uint8_t const *end = begin + len;
		queue_.insert(queue_.end(), begin, end);
		return len;
	}
};

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
