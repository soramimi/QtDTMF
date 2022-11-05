#include "Audio.h"

// Audio

QAudioFormat Audio::defaultAudioFormat()
{
	QAudioFormat format;
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
	format.setByteOrder(QAudioFormat::LittleEndian);
	format.setChannelCount(2);
	format.setCodec("audio/pcm");
	format.setSampleRate(48000);
	format.setSampleSize(16);
	format.setSampleType(QAudioFormat::SignedInt);
#else
	format.setChannelCount(2);
	format.setSampleRate(48000);
	format.setSampleFormat(QAudioFormat::Int16);
#endif
	return format;
}

// AudioDevice

AudioDevice::AudioDevice(const audio_device_t &dev)
	: device_(dev)
{
}

QString AudioDevice::text() const
{
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
	return device_.deviceName();
#else
	return device_.description();
#endif
}

// AudioDevices

void AudioDevices::fetchDevices(Mode mode)
{
	devices_.clear();
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
	QList<QAudioDeviceInfo> devs;
	switch (mode) {
	case AudioInput:
		devs = QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
		break;
	case AudioOutput:
		devs = QAudioDeviceInfo::availableDevices(QAudio::AudioOutput);
		break;
	}
	for (QAudioDeviceInfo const &d : devs) {
		devices_.emplace_back(d);
	}
#else
	QList<QAudioDevice> devs;
	switch (mode) {
	case AudioInput:
		devs = QMediaDevices::audioInputs();
		break;
	case AudioOutput:
		devs = QMediaDevices::audioOutputs();
		break;
	}
	for (QAudioDevice const &d : devs) {
		devices_.emplace_back(d);
	}
#endif
}

int AudioDevices::size() const
{
	return (int)devices_.size();
}

AudioDevice AudioDevices::device(int i)
{
	if (i >= 0 && i < (int)devices_.size()) {
		return devices_[i];
	}
	return {};
}

AudioDevice AudioDevices::defaultAudioInputDevice()
{
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
	return AudioDevice::audio_device_t(QAudioDeviceInfo::defaultInputDevice());
#else
	return AudioDevice::audio_device_t(QMediaDevices::defaultAudioInput());
#endif
}

AudioDevice AudioDevices::defaultAudioOutputDevice()
{
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
	return AudioDevice::audio_device_t(QAudioDeviceInfo::defaultOutputDevice());
#else
	return AudioDevice::audio_device_t(QMediaDevices::defaultAudioOutput());
#endif
}

