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

#endif // AUDIO_H
