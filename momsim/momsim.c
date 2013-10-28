#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "../wingop.h"

double t[11] = {20, 18, 16, 14, 12, 10, 8, 6, 4, 2, 0};

double l[11] = {.1, .2, .3, .4, .5, .6, .65, .6, .4, .2};

double d[11] = {.05, .07, .09, .11, .13, .15, .2, .3, .5, 1};

#define C .1
#define RHO 1.225
#define B 1
#define D .6
#define Z .2
#define W 7

/*double thrust(double v)
{
	if(v < 0)
	{
		return -1;
	}
	else if(v > 9)
	{
		return -1;
	}
	else if(round(v) == v)
	{
		return t[(int) v];
	}
	else
	{
		return t[(int) floor(v)] + (t[(int) ceil(v)] - t[(int) floor(v)])*((v - floor(v))/(ceil(v) - floor(v)));
	}
}

double lift(double a)
{
	if(a < 0)
 	{
 		return -1;
 	}
 	else if(a > 9)
	{
		return -1;
	}
	else if(round(a) == a)
	{
		return l[(int) a];
	}
	else
	{
		return l[(int) floor(a)] + (l[(int) ceil(a)] - l[(int) floor(a)])*((a - floor(a))/(ceil(a) - floor(a)));
	}
}

double drag(double a)
{
	if(a < 0)
        {
                return -1;
        }
        else if(a > 10)
        {
                return 0;
        }
        else if(round(a) == a)
        {
                return d[(int) a];
        }
        else
        {
                return d[(int) floor(a)] + (d[(int) ceil(a)] - d[(int) floor(a)])*((a - floor(a))/(ceil(a) - floor(a)));
        }
}*/

int main(int argc, char** argv)
{
	double alpha = 0;
	double maxa = 0;
	double maxcl = 0;
	while(1)
	{
		if(s1223cl(alpha+1, 0, 0) > s1223cl(alpha, 0, 0))
		{
			maxa = alpha + 1;
			maxcl = s1223cl(maxa, 0, 0);
		}
		alpha++;
		if(alpha > MAXALPHA)
		{
			break;
		}
	}
	
	printf("Max Cl is %g at alpha %g.\n", maxcl, maxa);
	return 0;
}
