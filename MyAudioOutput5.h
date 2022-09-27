#ifndef MYAUDIOOUTPUT5_H
#define MYAUDIOOUTPUT5_H

#include <memory>

class QAudioOutput;
class QIODevice;

class MyAudioOutput5 {
public:
	int volume = 5000;
	int sample_fq = 8000;
	std::shared_ptr<QAudioOutput> audio_output;
	QIODevice *device = nullptr;
	void start();
};

#endif // MYAUDIOOUTPUT5_H
