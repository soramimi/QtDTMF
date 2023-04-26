#include "Generator.h"
#include <QTime>

void Generator::start(int sample_rate)
{
	sample_rate_ = sample_rate;
	sine_curve_lo_.sample_rate = sample_rate;
	sine_curve_hi_.sample_rate = sample_rate;

	buffer_.resize(BUFLEN);

	open(QIODevice::ReadOnly);
}

void Generator::stop()
{
	close();
}

qint64 Generator::readData(char *data, qint64 len)
{
	int16_t *dst = (int16_t *)data;
	int n = len / sizeof(int16_t);
	if (n > 0) {
		const int N = (int)buffer_.size();
		n = std::min(n, (int)buffer_.size());
		for (int i = 0; i < n; i++) {
			double a = sine_curve_lo_.next();
			double b = sine_curve_hi_.next();
			int16_t v = (int16_t)((a + b) * volume_);
			dst[i] = v;

			buffer_[position_] = v;
			position_ = (position_ + 1) % N;
			if (position_ == 0) {
				emit notify(n, buffer_.data());
			}
		}
		return n * (int)sizeof(int16_t);
	}
	return 0;
}

qint64 Generator::writeData(const char *data, qint64 len)
{
	Q_UNUSED(data);
	Q_UNUSED(len);
	return 0;
}

qint64 Generator::bytesAvailable() const
{
	return buffer_.size();
}

