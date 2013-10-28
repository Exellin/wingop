#include "wingop.h"

#define RUNWAY 61

double takeoffd(double a1, double a2, double c1, double c2, double b1, double b2, double d, double z, double m, double step)
{
	double s1 = b1*c1;
       	double s2 = b2*c2;
        double ar1 = b1/c1;
        double ar2 = b2/c2;
	double ai1 = a1 - (s1223cl(a1, step, c1)/(M_PI*ar1))*(180/M_PI);
	double ai2 = a2 - (s1223cl(a2, step, c2)/(M_PI*ar2))*(180/M_PI) - (s1223cl(ai1, step, c1)/(2*M_PI*ar1) * ( ((1+(2*d/b1))/((pow(1+(2*d/b1),2)+pow((2*z/b1),2)))) + ((1-(2*d/b1))/((pow(1-(2*d/b1),2)+pow((2*z/b1),2)))) ) )*180/M_PI;
	double vn = 0;
	double vn1 = step;
	double distn = 0;
	double distn1 = 0;
	double tod = -1;
	double time = 0;
	while(vn1 > vn)
	{
		vn = vn1;
		double ai1 = a1 - (s1223cl(a1, vn, c1)/(M_PI*ar1))*(180/M_PI);
		double ai2 = a2 - (s1223cl(a2, vn, c2)/(M_PI*ar2))*(180/M_PI) - (s1223cl(ai1, step, c1)/(2*M_PI*ar1) * ( ((1+(2*d/b1))/((pow(1+(2*d/b1),2)+pow((2*z/b1),2)))) + ((1-(2*d/b1))/((pow(1-(2*d/b1),2)+pow((2*z/b1),2)))) ) )*180/M_PI;
		double l1 = lift(s1, ai1, vn, c1);
		double l2 = lift(s2, ai2, vn, c2);
		//printf("Dist: %gm, Speed: %gm/s, Lift: %gN, Drag: %gN, Thrust: %gN, Time: %gs\n", distn, vn, 2*(l1 + l2), drag(ai1, ai2, s1, s2, ar1, ar2, l1, l2, vn), thrust(vn), time);
		if(2*(l1 + l2) >= m*G)
		{
			tod = distn;
			break;
		}
		vn1 = ((thrust(vn) - drag(c1, c2, ai1, ai2, s1, s2, ar1, ar2, l1, l2, vn))/m)*(step) + vn;
		distn1 = distn + .5*step*(vn1 + vn);
		distn = distn1;
		time += step;
		if(distn > 61)
		{
			break;
		}
	}
	return tod;
}
