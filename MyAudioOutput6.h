#ifndef MYAUDIOOUTPUT6_H
#define MYAUDIOOUTPUT6_H
#include <QAudioDevice>
#include <memory>

class QAudioOutput;
class QAudioSink;

class MyAudioOutput {
public:
	int volume = 5000;
	int sample_fq = 8000;
	QAudioDevice device_;
	std::shared_ptr<QAudioOutput> output_;
	std::shared_ptr<QAudioSink> sink_;

	void start(QIODevice *out);
};

#endif // MYAUDIOOUTPUT6_H
