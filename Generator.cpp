#include "Generator.h"
#include "pi2.h"
#include <QTime>

void Generator::start()
{
	open(QIODevice::ReadOnly);
}

void Generator::stop()
{
	close();
}

qint64 Generator::readData(char *data, qint64 len)
{
	int16_t *dst = (int16_t *)data;
	size_t n = len / sizeof(int16_t);
	if (n > 0) {
		double a = sine_curve_lo.next();
		double b = sine_curve_hi.next();
		int16_t v = (int16_t)((a + b) * volume);
		dst[0] = v;

		buffer[index] = v;
		index = (index + 1) % 96;
		if (index == 0) {
			emit notify(96, buffer);
		}
		return sizeof(int16_t);
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
	return 2;
}

qint64 Generator::size() const
{
	return 2;
}

