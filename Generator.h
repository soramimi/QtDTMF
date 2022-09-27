#ifndef GENERATOR_H
#define GENERATOR_H

#include "SineCurve.h"

#include <QAudioFormat>
#include <QIODevice>


class Generator : public QIODevice {
	Q_OBJECT
private:
	SineCurve sine_curve_lo;
	SineCurve sine_curve_hi;
	int sample_fq = 8000;
	int volume = 5000;
	int16_t buffer[96];
	int index = 0;
public:
	void start();
	void stop();

	qint64 readData(char *data, qint64 len) override;
	qint64 writeData(const char *data, qint64 len) override;
	qint64 bytesAvailable() const override;
	qint64 size() const override;

	void setTone(int lo_fq, int hi_fq)
	{
		sine_curve_lo.tone_fq = lo_fq;
		sine_curve_hi.tone_fq = hi_fq;
	}
signals:
	void notify(int n, int16_t const *p);
};



#endif // GENERATOR_H
