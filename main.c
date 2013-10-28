#include "wingop.h"

#define MINM 7
#define MAXM 29.4835

#define MINA 0
#define MAXA 2
#define MINC .13
#define MAXC .35
#define MINB 1
#define MAXB 2
#define MIND .2
#define MAXD 1
#define MINDEM 3.9
#define MINZ 0
#define MAXZ .3
#define MAXDIFF .2


double A1 = 0;
double A2 = 0;
double C1 = 0;
double C2 = 0;
double B1 = 0;
double B2 = 0;
double D = 0;
double Z = 0;

int main(int argc, char** argv)
{
	
	double m;
	double maxm = 0;
	double inc = atof(argv[1]);
	double c1, c2;
	long unsigned config = 0;
	for(c1 = MINC; c1 <= MAXC; c1 += inc)
	{
		c2 = c1;
		double b1;
		for(b1 = MINB; b1 <= MAXB; b1 += inc)
		{
			if(c1+c2+2*b1+FUSEW+ENGL+LANDH >= MDEM)
               		{
               			config++;
				continue;
               		}
			
			double b2;
			double bigspan = b1;
			for(b2 = MINB; b2 <= MAXB; b2 += inc)
			{
				if(fabs(b2-b1) > MAXDIFF)
				{
					
					config++;
					continue;
				}
				if(b2 > b1)
				{
					bigspan = b2;
	
					if(c1+c2+2*b2+FUSEW+ENGL+LANDH >= MDEM)
					{
						config++;
						continue;
					}
				}
				double d;
				for(d = MIND; d <= MAXD; d += inc)
				{
					if(c1+c2+2*bigspan+FUSEW+ENGL+LANDH >= MDEM)
					{
						config++;
						continue;
					}
					double z;
					for(z = MINZ; z <= MAXZ; z+= inc)
					{
						if(c1+c2+2*bigspan+FUSEW+ENGL+LANDH >= MDEM)
						{
							config++;
							continue;
						}
						else if(c1+c2+2*bigspan+FUSEW+ENGL+LANDH < MINDEM)
						{
							config++;
							continue;
						}
						double a1;
						for(a1 = MINA; a1 <= MAXA; a1++)
						{
							double a2;
							for(a2 = MINA; a2 <= MAXA; a2++)
							{
								printf("Testing config: #%lu a1: %g, a2: %g, c1: %g, c2: %g, b1: %g, b2: %g, d: %g, z: %g", config, a1, a2, c1, c2, b1, b2, d, z);
								char stab = checkstab(a1, a2, c1, c2, b1, b2, d, z);
								if(stab < 0)
								{
									printf(" NOT STABLE               \r");
									config++;
									continue;
								}
								for(m = MINM; m <= MAXM; m += inc)
								{	
									double tod = takeoffd(a1, a2, c1, c2, b1, b2, d, z, m, inc);
									if(tod < 0)
									{
										printf(" CAN'T TAKE OFF   \r");
									}
									config++;
									if((tod > 0) && (m > maxm))
									{	
										maxm = m;
										A1 = a1;
										A2 = a2;
										C1 = c1;
										C2 = c2;
										B1 = b1;
										B2 = b2;
										D = d;
										Z = z;
										printf("\nHighest takeoff weight: %g. a1: %g, a2: %g, c1: %g, c2: %g, b1: %g, b2: %g, d: %g, z: %g\n", maxm, A1, A2, C1, C2, B1, B2, D, Z);
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return 0;
}
