#include "../wingop.h"

#define MAXF 25

double t[11] = {20, 18, 16, 14, 12, 10, 8, 6, 4, 2, 0}; //1 ms steps
//Arrays are deflection first (from -25 upwards) in increments of 5 degrees, then angle of attack (from 0, in 1 degree increments)
double l[11][21] = { //Lift coeffcient array
{-0.734, -0.577, -0.469, -0.357, -0.246, -0.137, -0.028, 0.079, 0.182, 0.282, 0.381, 0.479, 0.555, 0.641, 0.724, 0.798, 0.864, 0.917, 0.952, 0.972, 0.976},
{-0.51, -0.365, -0.254, -0.143, -0.032, 0.077, 0.184, 0.286, 0.384, 0.481, 0.577, 0.667, 0.733, 0.813, 0.886, 0.948, 0.998, 1.029, 1.044, 1.043, 1.027},
{-0.278, -0.148, -0.036, 0.075, 0.184, 0.291, 0.393, 0.488, 0.582, 0.676, 0.767, 0.825, 0.904, 0.974, 1.033, 1.08, 1.106, 1.116, 1.11, 1.088, 1.054},
{-0.041, 0.074, 0.185, 0.294, 0.402, 0.505, 0.596, 0.685, 0.777, 0.873, 0.918, 0.994, 1.062, 1.118, 1.161, 1.183, 1.188, 1.176, 1.149, 1.109, 1.059},
{0.198, 0.297, 0.407, 0.514, 0.618, 0.71, 0.792, 0.879, 0.989, 1.011, 1.085, 1.15, 1.204, 1.243, 1.26, 1.26, 1.243, 1.211, 1.165, 1.109, 1.047},
{0.437, 0.521, 0.628, 0.733, 0.829, 0.905, 0.982, 1.112, 1.104, 1.176, 1.238, 1.288, 1.324, 1.337, 1.332, 1.31, 1.272, 1.221, 1.16, 1.092, 1.021},
{0.675, 0.747, 0.85, 0.954, 1.026, 1.088, 1.167, 1.196, 1.265, 1.325, 1.373, 1.405, 1.414, 1.404, 1.377, 1.333, 1.277, 1.211, 1.138, 1.062, 0.986},
{0.91, 0.974, 1.072, 1.157, 1.202, 1.268, 1.288, 1.355, 1.412, 1.456, 1.485, 1.49, 1.476, 1.443, 1.395, 1.333, 1.262, 1.185, 1.104, 1.024, 0.945},
{1.143, 1.243, 1.311, 1.337, 1.372, 1.378, 1.443, 1.497, 1.539, 1.566, 1.566, 1.548, 1.511, 1.457, 1.391, 1.315, 1.232, 1.148, 1.063, 0.98, 0.902},
{1.37, 1.466, 1.499, 1.487, 1.471, 1.53, 1.582, 1.621, 1.643, 1.642, 1.619, 1.578, 1.52, 1.449, 1.368, 1.282, 1.192, 1.103, 1.017, 0.935, 0.857},
{1.588, 1.682, 1.646, 1.881, 1.615, 1.665, 1.702, 1.723, 1.718, 1.691, 1.646, 1.584, 1.508, 1.423, 1.332, 1.238, 1.145, 1.055, 0.969, 0.889, 0.814}
};

double d[11][21] = { //Drag coeffcient array
{0.05812, 0.05704, 0.05402, 0.07103, 0.0977, 0.09922, 0.10246, 0.10523, 0.11106, 0.12023, 0.1294, 0.13936, 0.15268, 0.16967, 0.19053, 0.2146, 0.2412, 0.27033, 0.29946, 0.34745, 0.3902},
{0.05476, 0.05467, 0.067, 0.08903, 0.08998, 0.09197, 0.0951, 0.10119, 0.10908, 0.11888, 0.12903, 0.13202, 0.1581, 0.17827, 0.20083, 0.22781, 0.25352, 0.29492, 0.32967, 0.39628, 0.46274},
{0.05291, 0.05524, 0.08139, 0.0828, 0.08469, 0.08795, 0.09215, 0.10061, 0.11065, 0.12096, 0.12195, 0.14681, 0.1668, 0.19028, 0.21544, 0.24297, 0.27887, 0.3251, 0.37204, 0.43022, 0.50206},
{0.05363, 0.07555, 0.07751, 0.0797, 0.08239, 0.08534, 0.09368, 0.10355, 0.11428, 0.11244, 0.13671, 0.15623, 0.17991, 0.20642, 0.23057, 0.26595, 0.30356, 0.36022, 0.43837, 0.51347, 0.57545},
{0.07021, 0.07418, 0.07649, 0.07952, 0.08306, 0.08833, 0.09826, 0.10914, 0.10506, 0.1296, 0.14845, 0.17113, 0.19799, 0.22456, 0.24508, 0.30699, 0.34407, 0.42275, 0.50063, 0.56154, 0.69323},
{0.07032, 0.07472, 0.07774, 0.08151, 0.08196, 0.09148, 0.10293, 0.09677, 0.12204, 0.14139, 0.16492, 0.18975, 0.21668, 0.25068, 0.29064, 0.34588, 0.40684, 0.46683, 0.53905, 0.69171, 0.77083},
{0.07277, 0.07738, 0.08102, 0.07982, 0.08818, 0.09979, 0.11185, 0.11556, 0.13367, 0.15619, 0.18218, 0.20425, 0.23942, 0.27258, 0.32308, 0.39131, 0.45884, 0.55226, 0.63327, 0.76157, 0.90476},
{0.07782, 0.08199, 0.08327, 0.08699, 0.09914, 0.11106, 0.11209, 0.12932, 0.15169, 0.17832, 0.20149, 0.22683, 0.28061, 0.33362, 0.38492, 0.45667, 0.57448, 0.61208, 0.74784, 0.9011, 1.04596},
{0.08467, 0.08797, 0.08783, 0.09713, 0.10948, 0.10802, 0.12588, 0.14628, 0.17029, 0.19811, 0.22155, 0.26279, 0.29594, 0.36597, 0.45706, 0.55092, 0.60027, 0.73287, 0.84026, 1.02297, 1.15846},
{0.09265, 0.09333, 0.0964, 0.10795, 0.1047, 0.12194, 0.14265, 0.16586, 0.18718, 0.21346, 0.25407, 0.30957, 0.35556, 0.44413, 0.52682, 0.62523, 0.74949, 0.8448, 1.00214, 1.07039, 1.32933},
{0.101, 0.09853, 0.10748, 0.10419, 0.11774, 0.13731, 0.16269, 0.18536, 0.21414, 0.24933, 0.28992, 0.35874, 0.437, 0.5043, 0.63755, 0.70259, 0.7831, 0.91095, 1.07004, 1.20569, 1.43685}
};

double m[11][21] = { //Moment coefficient array
{0.061, 0.067, 0.072, 0.124, 0.121, 0.118, 0.115, 0.111, 0.104, 0.099, 0.095, 0.091, 0.071, 0.064, 0.06, 0.056, 0.051, 0.044, 0.038, 0.034, 0.03},
{0.047, 0.05, 0.087, 0.084, 0.082, 0.079, 0.076, 0.072, 0.067, 0.063, 0.06, 0.056, 0.042, 0.038, 0.035, 0.032, 0.028, 0.022, 0.02, 0.018, 0.016},
{0.028, 0.032, 0.046, 0.044, 0.042, 0.04, 0.038, 0.034, 0.031, 0.029, 0.027, 0.019, 0.017, 0.015, 0.013, 0.01, 0.008, 0.006, 0.005, 0.004, 0.003},
{0.005, 0.007, 0.006, 0.004, 0.003, 0.001, 0, -0.002, -0.003, -0.005, -0.005, -0.006, -0.007, -0.007, -0.008, -0.008, -0.008, -0.008, -0.009, -0.009, -0.01},
{-0.033, -0.034, -0.035, -0.036, -0.037, -0.037, -0.036, -0.036, -0.039, -0.029, -0.028, -0.028, -0.028, -0.026, -0.023, -0.022, -0.022, -0.022, -0.022, -0.022, -0.023},
{-0.075, -0.076, -0.077, -0.077, -0.077, -0.074, -0.071, -0.078, -0.054, -0.052, -0.051, -0.049, -0.045, -0.039, -0.037, -0.036, -0.035, -0.035, -0.034, -0.034, -0.033},
{-0.115, -0.115, -0.115, -0.116, -0.111, -0.104, -0.101, -0.077, -0.073, -0.071, -0.069, -0.063, -0.054, -0.052, -0.048, -0.047, -0.047, -0.046, -0.046, -0.046, -0.043},
{-0.158, -0.155, -0.155, -0.152, -0.141, -0.134, -0.101, -0.095, -0.093, -0.089, -0.08, -0.068, -0.064, -0.061, -0.06, -0.057, -0.057, -0.056, -0.053, -0.055, -0.054},
{-0.201, -0.203, -0.198, -0.183, -0.167, -0.124, -0.118, -0.114, -0.11, -0.103, -0.086, -0.079, -0.074, -0.072, -0.071, -0.068, -0.067, -0.066, -0.065, -0.064, -0.063},
{-0.24, -0.242, -0.23, -0.204, -0.152, -0.139, -0.134, -0.129, -0.116, -0.1, -0.091, -0.087, -0.085, -0.082, -0.08, -0.08, -0.076, -0.073, -0.071, -0.072, -0.066},
{-0.278, -0.28, -0.254, -0.284, -0.16, -0.154, -0.149, -0.14, -0.123, -0.108, -0.099, -0.096, -0.094, -0.091, -0.089, -0.086, -0.086, -0.084, -0.082, -0.08, -0.079}
};

double preverr = 0; //For the PID controller, previous error
double integ = 0; //Current integral state for PID controller
//UNIT SYSTEM IS KG M S
#define C .1 //Chord
#define RHO 1.225 //Air density
#define B 1 //Span
#define D .6 //Distance horizontally
#define Z .2 //Distance vertically 
#define W 7.0 //Mass of aeroplane 

double pid(double, double, double, double, double, double); //Forward declaration

double linthrust(double v) //Thrust output
{
	if(v < 0) //No backwards
	{
		return -1;
	}
	else if(v > 9) //Thrust drops to zero at 9m/s
	{
		return 0;
	}
	else if(round(v) == v) //If it's an integer
	{
		return t[(int) v]; //Just cast it, no interpolation
	}
	else //If it's a double, linearly interpolate the thrust
	{
		return t[(int) floor(v)] + (t[(int) ceil(v)] - t[(int) floor(v)])*((v - floor(v))/(ceil(v) - floor(v)));
	}
}

double clarkl(double a, double f) //Lift coefficient from the wing
{
	if(a < 0) //No negative angle of attack
 	{
 		return -1;
 	}
 	else if(a > 20) //Angle of attack cannot exceed 20
	{
		return -1;
	}
	else if(f <= -25) //Deflection cannot be lower than -24
	{
		return -1;
	}
	else if(f > 25) //Deflection cannot exceed 25 degrees
	{
		return -1;
	}
	else if((round(a) == a) && (round(f) == f)) //If both are effectively integers
	{
		f = round((-f+25)/5); //Divide the defection by 5
		return l[(int) f][(int) a]; //Just return the values in the array
	}
	else if((round(a) == a) && !(round(f) == f)) //If AoA is integer but deflection is a decimal
	{
		f = ((-f+25)/5); //Convert f to correct index
		if(f == 0) //f being zero sometimes explodes things
		{
			f = .0001;
		}
		printf("f: %g\n", f); //Debugging use
		return l[(int)(floor(f))][(int) a] + (l[(int)(ceil(f))][(int) a] - l[(int)(floor(f))][(int) a])*((f-floor(f))/(ceil(f)-floor(f))); //Linear interpolation for a
	}
	else if(!(round(a) == a) && (round(f) == f)) //Same as above for a being a decimal
	{
		f = round((-f+25)/5);
		if(a == 0)
		{
			a = .0001;
		}
		return l[(int) f][(int)(floor(a))] + (l[(int) f][(int)(ceil(a))] - l[(int) f][(int)(floor(a))])*((a-floor(a))/(ceil(a)-floor(a)));
	}
	else //If both are decimals (oh dear)
	{
		f = (-f+25)/5; //Convert f
		printf("f: %g\n", f);
		if(a == 0) //If either is zero, we get a division by zero.
		{
			a = .0001;
		}
		if(f == 0)
		{
			f = .0001;
		}
		return (1/( (ceil(a) - floor(a)) * (ceil(f) - floor(f)) )) * ( (l[(int) floor(f)][(int) floor(a)]*(ceil(a) - a)*(ceil(f) - f)) + (l[(int) ceil(f)][(int) floor(a)]*(a - floor(a))*(ceil(f) - f)) + (l[(int) floor(f)][(int) ceil(a)]*(ceil(a) - a)*(f - floor(f))) + (l[(int) ceil(a)][(int) ceil(f)]*(a - floor(a))*(f - floor(f))) ); //Bilinear interpolation (ew)
	}
}

double clarkd(double a, double f) //See clarkl. Drag coeff
{
	if(a < 0)
        {
                return -1;
        }
        else if(a > 20)
        {
                return -1;
        }
        else if(f <= -25)
        {
                return -1;
        }
        else if(f > 25)
        {
                return -1;
        }
        else if((round(a) == a) && (round(f) == f))
        {
                f = round((-f+25)/5);
		return d[(int) f][(int) a];
        }
	 else if((round(a) == a) && !(round(f) == f))
 	{
		f = ((-f+25)/5);
		if(f == 0)
		{
			f = .0001;
		}
		return d[(int)(floor(f))][(int) a] + (d[(int)(ceil(f))][(int) a] - d[(int)(floor(f))][(int) a])*((f-floor(f))/(ceil(f)-floor(f)));
 	}
 	else if(!(round(a) == a) && (round(f) == f))
 	{
        	f = round((-f+25)/5);
		if(a == 0)
		{
			a = .0001;
		}
		return d[(int) f][(int)(floor(a))] + (d[(int) f][(int)(ceil(a))] - d[(int) f][(int)(floor(a))])*((a-floor(a))/(ceil(a)-floor(a)));
 	}
        else
        {
		f = (-f+25)/5;
		if(a == 0)
		{
			a = .0001;
		}
		if(f == 0)
		{
			f = .0001;
		}
		return (1/( (ceil(a) - floor(a)) * (ceil(f) - floor(f)) )) * ( (d[(int) floor(f)][(int) floor(a)]*(ceil(a) - a)*(ceil(f) - f)) + (d[(int) ceil(f)][(int) floor(a)]*(a - floor(a))*(ceil(f) - f)) + (d[(int) floor(f)][(int) ceil(a)]*(ceil(a) - a)*(f - floor(f))) + (d[(int) ceil(a)][(int) ceil(f)]*(a - floor(a))*(f - floor(f))) );
	}
}

double clarkm(double a, double f) //See clarkl. Moment coeff
{
        if(a < 0)
        {
                return -1;
        }
        else if(a > 20)
        {
                return -1;
        }
        else if(f <= -25)
        {
                return -1;
        }
        else if(f > 25)
        {
                return -1;
        }
        else if((round(a) == a) && (round(f) == f))
        {
		f = round((-f+25)/5);
		return m[(int) f][(int) a];
        }
	else if((round(a) == a) && !(round(f) == f))
 	{
		f = ((-f+25)/5);
		if(f == 0)
		{
			f = .0001;
		}
		return m[(int)(floor(f))][(int) a] + (m[(int)(ceil(f))][(int) a] - m[(int)(floor(f))][(int) a])*((f-floor(f))/(ceil(f)-floor(f)));
 	}
 	else if(!(round(a) == a) && (round(f) == f))
 	{
		f = round((-f+25)/5);
		if(a == 0)
		{
			a = .0001;
		}
        	return m[(int) f][(int)(floor(a))] + (m[(int) f][(int)(ceil(a))] - m[(int) f][(int)(floor(a))])*((a-floor(a))/(ceil(a)-floor(a)));
 	}
        else
        {
		f = (-f+25)/5;
		if(a == 0)
		{
			a = .0001;
		}
		if(f == 0)
		{
			f = .0001;
		}
                return (1/( (ceil(a) - floor(a)) * (ceil(f) - floor(f)) )) * ( (m[(int) floor(f)][(int) floor(a)]*(ceil(a) - a)*(ceil(f) - f)) + (m[(int) ceil(f)][(int) floor(a)]*(a - floor(a))*(ceil(f) - f)) + (m[(int) floor(f)][(int) ceil(a)]*(ceil(a) - a)*(f - floor(f))) + (m[(int) ceil(a)][(int) ceil(f)]*(a - floor(a))*(f - floor(f))) );
        }
}



int main(int argc, char** argv) //argc is argument count, argv is an array of space delimited argument strings
{
	double alpha = 0; //Initial AoA
	double maxa = 0; //Stall maxa
	double maxcl = 0; //Stall Coeff lift
	while(1) //Finds stall Cl
	{
		printf("Alpha: %g Cl: %g\n", alpha, clarkl(alpha, 0));
		if(clarkl(alpha, 0) > maxcl)
		{
			maxa = alpha;
			maxcl = clarkl(alpha, 0);
		}
		alpha++;
		if(alpha > 20)
		{
			break;
		}
	}
	
	printf("Max Cl is %g at alpha %g.\n", maxcl, maxa);
	//double flap;
	double maxdist = 61; //Runway length
	double ts = .01; //Time step
	double vn = 0; //Previous velocity
	double vn1 = ts; //New velocity
	double distn = 0; //Current distance
	double tod = -1; //take off distance
	double time = 0; //Time taken
	alpha = 0; //Reset AoA to zero
	double deflec = 0; //Flap deflection
	double angv = 0; //Current angular velocity
	double angv1 = ts; //New angular veolcity
	while(1)
	{
		printf("Alpha: %g, Deflec: %g\n", alpha, deflec);
		vn = vn1;
		angv = angv1;
		double fclift = .5*RHO*pow(vn, 2)*clarkl(alpha, 0)*B*C; //Calculating lift, front wing
		puts("1");
		double fcdrag = .5*RHO*pow(vn, 2)*clarkd(alpha, 0)*B*C;
		puts("2");
		double rclift = .5*RHO*pow(vn, 2)*clarkl(alpha, deflec)*B*C; //Back wing
		puts("3");
		double rcdrag = .5*RHO*pow(vn, 2)*clarkd(alpha, deflec)*B*C;
		puts("4");
		if((2*fclift + 2*rclift) > W*G) //See if it takes off
		{
			printf("Takeoff!\n");
			break;
		}
		vn1 = ((linthrust(vn) - (2*fcdrag+2*rcdrag))/W)*ts + vn; //Numerical integral for speed
		puts("5");
		distn = distn + .5*ts*(vn1 + vn); //Numerical integral for distance
		time += ts;
		if(distn > maxdist) //If we exceed runway length, fail
		{
			printf("No takeoff.\n");
			break;
		}
		deflec = pid(2, 1, 2, maxa, alpha, ts); //Put the current state into the PID controller and set the flap deflection
		puts("6");
		double fcmom = 2*C*C*B*clarkm(alpha, 0) + 2*fclift*D*.5; //Moment at the front wing
		printf("deflec: %g\n", deflec);
		double rcmom = 2*C*C*B*clarkm(alpha, deflec) + -2*rclift*D*.5; //Moment at the rear wing
		puts("7");
		angv1 = ((fcmom + rcmom)/W)*ts+angv1; //Angular numerical velocity integral
		alpha = (alpha + .5*ts*(angv + angv1))*(180/M_PI); //Numerical anglar position integral
		printf("%gs: Lift: %g Drag: %g Thrust: %g Speed: %g Distance: %g Alpha: %g Deflection:%g Moment: %g\n", time, (2*fclift + 2*rclift), (2*fcdrag + 2*rcdrag), linthrust(vn1), vn1, distn, alpha, deflec, (fcmom+rcmom));
	}
	return 0;
}

double pid(double kp, double ki, double kd, double sp, double mv, double ts) //PID controller for the plane
{
	double err = sp - mv; //Error from set point and measured value
	integ = integ + err*ts; //Integral (numerical)
	double deriv = (err - preverr)/ts; //Derivative (numerical)
	preverr = err; 
	if((kp*err + ki*integ + kd*deriv) >= MAXF)
	{
		return MAXF; //Maximum deflection
	}
	else if((kp*err + ki*integ + kd*deriv) <=-MAXF)
	{
		return -MAXF;
	}
	else
	{
		return (kp*err + ki*integ + kd*deriv); //Return the PID
	}
}
