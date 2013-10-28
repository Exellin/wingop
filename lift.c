#include "wingop.h"

const double s1223cla[51] = {-0.172,
-0.177,
-0.181,
-0.184,
-0.185,
-0.182,
-0.176,
-0.165,
-0.148,
-0.123,
-0.088,
-0.044,
0.013,
0.081,
0.161,
0.251,
0.35,
0.454,
0.562,
0.67,
0.778,
0.883,
0.983,
1.077,
1.456,
1.569,
1.683,
1.795,
1.906,
2.015,
2.121,
2.223,
2.194,
2.191,
2.251,
2.312,
2.407,
2.442,
2.459,
2.405,
2.321,
2.211,
2.072,
1.954,
1.804,
1.641,
1.439,
1.286,
1.165,
1.053,
0.951,
};

double s1223cl(double a, double v, double l)
{
	if(a < -25)
	{
		return s1223cla[0];
	}
	else if(a > 25)
	{
		return s1223cla[51];
	}
	double r = 0;
	if(round(a) != a)
	{
		r = s1223cla[(int)(floor(a)+25)] + (s1223cla[(int)(ceil(a)+25)] - s1223cla[(int)(floor(a)+25)])*((a-floor(a))/(ceil(a)-floor(a)));
	}
	else
	{
		r = s1223cla[(int)a+25];
	}
	return r;
}

double lift(double s, double a, double v, double c)
{
	return .5*RHO*pow(v,2)*s*s1223cl(a, v, c);
}

