#ifndef SINECURVE_H
#define SINECURVE_H

class SineCurve {
public:
	double sample_fq = 8000;
	double tone_fq = 0;
	double phase = 0;

	double next();
};

#endif // SINECURVE_H
