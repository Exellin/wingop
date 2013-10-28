#include "wingop.h"

const double s1223cda[51] = {0.6512,
0.84111,
0.4938,
0.45193,
0.41381,
0.42512,
0.37916,
0.33478,
0.28268,
0.25251,
0.21488,
0.18812,
0.16913,
0.13906,
0.11882,
0.10608,
0.09175,
0.08128,
0.07138,
0.06196,
0.05694,
0.05264,
0.04975,
0.04809,
0.02552,
0.02677,
0.02756,
0.02858,
0.02759,
0.02875,
0.0482,
0.0517,
0.05677,
0.06503,
0.0725,
0.08051,
0.08982,
0.1062,
0.12096,
0.13686,
0.15545,
0.17704,
0.20436,
0.22692,
0.25807,
0.29514,
0.35548,
0.36931,
0.41228,
0.46013,
0.52384,
};

double s1223cd(double a, double v, double l)
{
	if(a < -25)
        {
                return s1223cda[0];
        }
        else if(a > 25)
        {
                return s1223cda[51];
        }
	
	double r = 0;
	if(round(a) != a)
	{
		r = s1223cda[(int)(floor(a)+25)] + (s1223cda[(int)(ceil(a)+25)] - s1223cda[(int)(floor(a)+25)])*((a-floor(a))/(ceil(a)-floor(a)));
	}
	else
	{
		r = s1223cda[(int)a+25];
	}
	return r;
}

double drag(double c1, double c2, double a1, double a2, double s1, double s2, double ar1, double ar2, double l1, double l2, double v)
{

	double induceddrag1 = pow(2*l1,2)/(.5*RHO*pow(v,2)*4*s1*M_PI*E*ar1);
	double induceddrag2 = pow(2*l2,2)/(.5*RHO*pow(v,2)*4*s2*M_PI*E*ar2);
	double formdrag1 = 2*.5*RHO*pow(v,2)*s1*s1223cd(a1, v, c1);
	double formdrag2 = 2*.5*RHO*pow(v,2)*s2*s1223cd(a2, v, c2);
	double skindrag1 = 2*.5*RHO*pow(v,2)*s1*CF;
	double skindrag2 = 2*.5*RHO*pow(v,2)*s2*CF;
	double fusedrag = .5*RHO*FUSECD*pow(v,2)*pow((FUSEW/2),2)*M_PI;
	double tdrag = induceddrag1+induceddrag2+formdrag1+formdrag2+skindrag1+skindrag2+fusedrag;
	return tdrag;

} 
