#include "wingop.h"

#define TESTV 10

char checkstab(double a1, double a2, double c1, double c2, double b1, double b2, double d, double z)
{
	
	int stabalpha = -1;
	double minmon = 99999;
	int alpha;
	for(alpha = -20; alpha <= 20; alpha++)
	{
		double ai1 = alpha + a1 - (s1223cl((alpha+a1), TESTV, c1)/(M_PI*(b1/c1)))*(180/M_PI);
		double ai2 = alpha + a2 - (s1223cl((alpha+a2), TESTV, c2)/(M_PI*(b2/c2)))*(180/M_PI) - (s1223cl(ai1, TESTV, c1)/(2*M_PI*(b1/c1)) * ( ((1+(2*d/b1))/((pow(1+(2*d/b1),2)+pow((2*z/b1),2)))) + ((1-(2*d/b1))/((pow(1-(2*d/b1),2)+pow((2*z/b1),2)))) ) )*180/M_PI;
		double m1 = 2*c1*c1*b1*s1223cm(ai1, TESTV, c1);
		double m2 = 2*c2*c2*b2*s1223cm(ai2, TESTV, c2);
		double ml1 = 2*c1*b1*s1223cl(ai1, TESTV, c1)*(.5*d+(1-AC)*c1);
		double ml2 = -2*c2*b2*s1223cl(ai2, TESTV, c2)*(.5*d+AC*c2);
		double md2 = 2*c2*b2*s1223cd(ai2, TESTV, c2)*(z);
		double m = m1 + m2 + ml1 + ml2 + md2;
		if((alpha < 0) && (m < 0))
		{
			return -1;
		}
		if((alpha > 0) && (m > 0))
		{
			return -1;
		}
		if(fabs(m) < fabs(minmon))
		{
			minmon = m;
			stabalpha = alpha;
		}
	}
	if(stabalpha == 0)
	{
		return 0;
	}
	return -1; 
}

