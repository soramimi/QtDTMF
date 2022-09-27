#include "MyAudioOutput6.h"
#include <QAudioOutput>
#include <QAudioSink>
#include <QMediaDevices>


void MyAudioOutput::start(QIODevice *out)
{
	QAudioFormat format;
	format.setChannelCount(1);
	format.setSampleRate(8000);
	format.setSampleFormat(QAudioFormat::Int16);

	device_ = QMediaDevices::defaultAudioOutput();
	output_ = std::make_shared<QAudioOutput>(device_);
	sink_ = std::make_shared<QAudioSink>(device_, format);
	sink_->setBufferSize(1);
	sink_->start(out);
}

