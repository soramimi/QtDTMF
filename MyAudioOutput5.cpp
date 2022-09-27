#include "MyAudioOutput5.h"

#include <QAudioFormat>
#include <QAudioOutput>

void MyAudioOutput5::start()
{
	QAudioFormat format;
	format.setByteOrder(QAudioFormat::LittleEndian);
	format.setChannelCount(1);
	format.setCodec("audio/pcm");
	format.setSampleRate(sample_fq);
	format.setSampleSize(16);
	format.setSampleType(QAudioFormat::SignedInt);

	audio_output = std::make_shared<QAudioOutput>(format);
	audio_output->setBufferSize(2000);
	device = audio_output->start();
}
