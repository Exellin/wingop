#include "wingop.h"

#define MINM 7
#define MAXM 29.4835

#define MINA 0
#define MAXA 2
#define MINC .13
#define MAXC .35
#define MINB 1
#define MAXB 1.2
#define MIND .2
#define MAXD 1
#define MINDEM 3.9
#define MINZ 0
#define MAXZ .3
#define MAXDIFF .2
#define RUNWAY 61


double A1 = 0;
double A2 = 0;
double C1 = 0;
double C2 = 0;
double B1 = 0;
double B2 = 0;
double D = 0;
double Z = 0;

int main()
{	
	double m;
	double maxm = 0;
	double mintod = 100;
	// double inc = atof(argv[1]);  // What is atof?
	double inc = 0.01;
	double c1, c2;
	long unsigned config = 0;
	double tod = 0;
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
				double d = 3*C2; //Recommended from RC Model Aircraft Design
				double z = 0.5*C2; //Recommended from RC Model Aircraft Design
				double NP = ((2*b1*c1)*d)/(2*b1*c1+2*b2*c2); //distance from quarter chord of rear wing to neutral point
				double CG = NP + 0.01*c1; //distance from neutral point to CofG
				 if(c1+c2+2*bigspan+FUSEW+ENGL+LANDH >= MDEM) //|| c1+c2+2*bigspan+FUSEW+ENGL+LANDH < MINDEM) fix
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
						char stab = checkstab(a1, a2, c1, c2, b1, b2, d, z, NP, CG);
						if(stab < 0)
						{
						//	printf(" NOT STABLE               \r");
							config++;
							continue;
						}
						tod = momsim(a1, a2, c1, c2, b1, b2, d, z, 0, NP, CG);
						if(tod >= RUNWAY)
						{
							printf(" CAN'T TAKE OFF   \r");
						}
						config++;
						if(tod < mintod)
						{	
							mintod = tod;
							for(m = MINM; tod >= RUNWAY; m += 2)
							{	
								tod = momsim(a1, a2, c1, c2, b1, b2, d, z, m, NP, CG);
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
	printf("\nHighest takeoff weight: %g. a1: %g, a2: %g, c1: %g, c2: %g, b1: %g, b2: %g, d: %g, z: %g\n", maxm, A1, A2, C1, C2, B1, B2, D, Z);
	return 0;
}


