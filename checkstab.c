#include "wingop.h"

#define TESTV 10

char checkstab(double a1, double a2, double c1, double c2, double b1, double b2, double d, double z, double NP, double CG)
{
	
	int stabalpha = 0;
	//double minmon = 99999;
	int alpha;
	double mold;
	double mnew = 0;
	for(alpha = -10; alpha <= 10; alpha++)
	{
		double ai1 = alpha + a1 - (s1223cl((alpha+a1), TESTV, c1)/(M_PI*(b1/c1)))*(180/M_PI);
		double ai2 = alpha + a2 - (s1223cl((alpha+a2), TESTV, c2)/(M_PI*(b2/c2)))*(180/M_PI) - (s1223cl(ai1, TESTV, c1)/(2*M_PI*(b1/c1)) * ( ((1+(2*d/b1))/((pow(1+(2*d/b1),2)+pow((2*z/b1),2)))) + ((1-(2*d/b1))/((pow(1-(2*d/b1),2)+pow((2*z/b1),2)))) ) )*180/M_PI;
		double m1 = 2*c1*c1*b1*s1223cm(ai1, TESTV, c1);
		double m2 = 2*c2*c2*b2*s1223cm(ai2, TESTV, c2);
		double ml1 = 2*c1*b1*s1223cl(ai1, TESTV, c1)*(d-NP-CG);
		double ml2 = -2*c2*b2*s1223cl(ai2, TESTV, c2)*(NP+CG);
		double md1 = 0; //Assuming CG is in line with the front wing
		double md2 = 2*c2*b2*s1223cd(ai2, TESTV, c2)*(z);
		mold = mnew;
		mnew = m1 + m2 + ml1 + ml2 + md1 + md2;
		if((mnew - mold) > 0) //AoA is increasing, so moment should decrease
		{
			stabalpha = -1;
		}
		// if(fabs(mnew) < fabs(minmon))
		// {
			// minmon = mnew;
			// stabalpha = alpha;
		// }
	}
	if(stabalpha != -1)
	{
		return 0;
	}
	return -1; 
}

