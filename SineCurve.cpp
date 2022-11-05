#include "SineCurve.h"
#include "pi2.h"
#include <cmath>

double SineCurve::next()
{
	if (sample_rate == 0) return 0;
	if (tone_fq == 0) return 0;

	double ret = sin(phase);
	phase += PI2 * tone_fq / sample_rate;
	phase = fmod(phase, PI2);
	return ret;
}
