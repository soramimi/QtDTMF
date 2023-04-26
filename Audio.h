#ifndef AUDIO_H
#define AUDIO_H

#include <Qt>
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
#include "AudioInputQt5.h"
#include "AudioOutputQt5.h"
#include <QAudioDeviceInfo>
#else
#include "AudioInputQt6.h"
#include "AudioOutputQt6.h"
#include <QAudioDevice>
#include <QMediaDevices>
#endif

class Audio {
public:
	static QAudioFormat defaultAudioFormat();
};

class AudioDevice {
public:
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
	typedef QAudioDeviceInfo audio_device_t;
#else
	typedef QAudioDevice audio_device_t;
#endif
	audio_device_t device_;

	AudioDevice() = default;
	AudioDevice(audio_device_t const &dev);
	QString text() const;
};

class AudioDevices {
public:
	enum Mode {
		AudioInput,
		AudioOutput
	};

	std::vector<AudioDevice> devices_;

	void fetchDevices(Mode mode);
	int size() const;
	AudioDevice device(int i);
	static AudioDevice defaultAudioInputDevice();
	static AudioDevice defaultAudioOutputDevice();
};

class OutputBuffer : public QIODevice {
	friend class AudioOutput;
private:
	const int MINSIZE = 200;
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
		return std::max(MINSIZE, (int)queue_.size());
	}
public:
	void start()
	{
		open(QIODevice::ReadOnly);
	}
	qint64 bytesRemain() const
	{
		return (int)queue_.size();
	}
	void clearInput()
	{
		queue_.clear();
	}
	int writeInput(uint8_t const *ptr, int len)
	{
		uint8_t const *begin = (uint8_t const *)ptr;
		uint8_t const *end = begin + len;
		queue_.insert(queue_.end(), begin, end);
		return len;
	}
};

#endif // AUDIO_H
