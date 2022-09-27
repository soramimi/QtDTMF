#include "MyAudioOutput5.h"
#include <QAudioFormat>
#include <QAudioOutput>

void MyAudioOutput::start(QIODevice *gen)
{
	(void)gen;

	QAudioFormat format;
	format.setByteOrder(QAudioFormat::LittleEndian);
	format.setChannelCount(1);
	format.setCodec("audio/pcm");
	format.setSampleRate(sample_fq_);
	format.setSampleSize(16);
	format.setSampleType(QAudioFormat::SignedInt);

	output_ = std::make_shared<QAudioOutput>(format);
	output_->setBufferSize(2000);
	device_ = output_->start();
}

