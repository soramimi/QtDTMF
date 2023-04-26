#ifndef GENERATOR_H
#define GENERATOR_H

#include "SineCurve.h"
#include <QAudioFormat>
#include <QIODevice>

class Generator : public QIODevice {
	Q_OBJECT
private:
	int volume_ = 5000;
	int sample_rate_ = 8000;
	int BUFLEN = 160;
	std::vector<int16_t> buffer_;
	SineCurve sine_curve_lo_;
	SineCurve sine_curve_hi_;
	int position_ = 0;
public:
	void start(int sample_rate);
	void stop();

	qint64 readData(char *data, qint64 len) override;
	qint64 writeData(const char *data, qint64 len) override;
	qint64 bytesAvailable() const override;

	void setTone(int lo_fq, int hi_fq)
	{
		sine_curve_lo_.tone_fq = lo_fq;
		sine_curve_hi_.tone_fq = hi_fq;
	}
signals:
	void notify(int n, int16_t const *p);
};



#endif // GENERATOR_H
