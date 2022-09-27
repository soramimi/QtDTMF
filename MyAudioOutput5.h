#ifndef MYAUDIOOUTPUT5_H
#define MYAUDIOOUTPUT5_H
#include <memory>

class QAudioOutput;
class QIODevice;

class MyAudioOutput {
public:
	int volume_ = 5000;
	int sample_fq_ = 8000;
	std::shared_ptr<QAudioOutput> output_;
	QIODevice *device_ = nullptr;
	void start(QIODevice *gen);
};

#endif // MYAUDIOOUTPUT5_H
