#include "../wingop.h"

#define MAXF 25

double t[11] = {20, 18, 16, 14, 12, 10, 8, 6, 4, 2, 0}; //1 ms steps.  Isn't this 2?

double preverr = 0; //For the PID controller, previous error
double integ = 0; //Current integral state for PID controller
//UNIT SYSTEM IS KG M S
#define C .1 //Chord
#define RHO 1.225 //Air density
#define B 1 //Span
#define D .6 //Distance horizontally
#define Z .2 //Distance vertically 
#define M 7.0 //Mass of aeroplane 
#define MU .00001796

void defleccoefficients(double Re, double alpha, double deflec, double* Cldeflecpointer, double* Cddeflecpointer, double* Cmdeflecpointer);
double pid(double, double, double, double, double, double); //Forward declaration
double findmaxalpha(double Re, double alpha, double deflec);

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

double findmaxalpha(double Re, double alpha, double deflec)  //only finds max angle of attack at the rounded values.
{
int i = 0;
double Cltest = 0;		
double Clprevious = 0;	// to guarantee the first point won't have a lower Cl since it is negative
double alphatest = 0;
char file_name[25] = ""; 	//initializing filename with an empty string
char blanktest = ' ';		//testing for blanks when reading file
char Restring[25];			//variable that will hold Reynolds number as a string
char Restringtrunc[25]; 	//Reynolds number rounded to nearest 5000
char alphastring[25] = "";	//angle of attack string
char deflecstring[25] = "";
int Reincrement = 5000; 
char line[100];				//string to hold line of file
int KeepLooping = 1;
char Clstring[25] = "";
FILE *filepointer;

strcat(file_name, "./s1223rawdata/"); 						//1st part of filename
Re = floor(Re/Reincrement)*Reincrement; 					//rounding to nearest 5000, to a minimum of 5000
if (Re < 5000)
{
Re = 5000;
}
alpha = round(alpha);										//rounding to nearest integer
deflec = floor(deflec/5)*deflec;							//rounding to nearest 5
sprintf(deflecstring, "%d", (int) deflec);
sprintf(Restring, "%lf", Re/1000000); 						//converting to string
strncpy(Restringtrunc, Restring, 5);						//truncating to 5 digits
Restringtrunc[5] = '\0'; 									//adding 0 to make it a string
strcat(file_name, deflecstring);
strcat(file_name, "s1223_T0_Re");
strcat(file_name, Restringtrunc); 							
strcat(file_name, "_M0.00_N9.0.txt "); 						
printf("%s\n", file_name);	

filepointer = fopen(file_name, "r"); //read mode
if (filepointer == NULL)
{
	perror("Error while opening the file.\n");
	exit(EXIT_FAILURE);
}

while(1 && KeepLooping)			
{
	while (fgets(line, 100, filepointer) && KeepLooping)
	{
		memset(alphastring, '\0', strlen(alphastring));
		memset(Clstring, '\0', strlen(Clstring));
		i = 0;
		//printf("fgets contains %s", line);
		while (blanktest == ' ') //read AoA
		{
			blanktest = line[i];
			i++;
		}
		while (blanktest != ' ')
		{
			alphastring[strlen(alphastring)] = blanktest;
			blanktest=line[i];
			i++;
		}
		sscanf(alphastring, "%lf", &alphatest);

		while (blanktest == ' ') //read CL
		{
			blanktest = line[i];
			i++;
		}	
		while (blanktest != ' ')
		{
			Clstring[strlen(Clstring)] = blanktest;
			//printf("Clstring is %s\n", Clstring);
			blanktest=line[i];
			i++;
		}
		if (alphastring[strlen(alphastring)-1] == '0') //guarantee it is data
		{

			Clprevious = Cltest;
			sscanf(Clstring, "%lf", &Cltest);
			//printf("at an aoa of %lf, the Cl is %lf and Clprevious is %lf\n", alphatest, Cltest, Clprevious);
			if (Cltest < Clprevious && Cltest >0) //testing if Cl has decreased after going positive
			{
				KeepLooping = 0;
				fclose(filepointer);
				return alphatest;
			}
		}
	}
	if (feof(filepointer)) //with 3 blank lines at end of file, alphastring is 25.000 3 times until the file ends.
	{
		KeepLooping = 0;
	}
}
fclose(filepointer);
printf("There was no maximum Cl\n");
return alphatest;
}

void updatecoefficients(double Re, double alpha, double deflec, double* Clpointer, double* Cdpointer, double* Cmpointer)
{
double precision = 0.0001;
int i = 0;
double alphatest;
char file_name[25] = ""; 	//initializing filename with an empty string
char blanktest = ' ';		//testing for blanks when reading file
char Restring[25];			//variable that will hold Reynolds number as a string
char Restringtrunc[25]; 	//Reynolds number rounded to nearest 5000
char alphastring[25] = "";	//angle of attack string
char deflecstring[25] = "";
int Reincrement = 5000; 
char line[100];				//string to hold line of file
char Clstring[25] = "";
char Cdstring[25] = "";
char Cmstring[25] = "";
int KeepLooping = 1;
FILE *filepointer;

strcat(file_name, "./s1223rawdata/"); 						//1st part of filename
Re = floor(Re/Reincrement)*Reincrement; 					//rounding to nearest 5000, to a minimum of 5000
if (Re < 5000)
{
Re = 5000;
}
alpha = round(alpha);										//rounding to nearest integer
deflec = floor(deflec/5)*deflec;							//rounding to nearest 5
sprintf(deflecstring, "%d", (int) deflec);
sprintf(Restring, "%lf", Re/1000000); 						//converting to string
strncpy(Restringtrunc, Restring, 5);						//truncating to 5 digits
Restringtrunc[5] = '\0'; 									//adding 0 to make it a string
strcat(file_name, deflecstring);
strcat(file_name, "s1223_T0_Re");
strcat(file_name, Restringtrunc); 							
strcat(file_name, "_M0.00_N9.0.txt "); 						
printf("%s\n", file_name);	

filepointer = fopen(file_name, "r"); //read mode
if (filepointer == NULL)
{
	perror("Error while opening the file.\n");
	exit(EXIT_FAILURE);
}

while(1 && KeepLooping)			
{
	while (fgets(line, 100, filepointer) && KeepLooping)
	{
		memset(alphastring, '\0', strlen(alphastring));
		i = 0;
		//printf("fgets contains %s", line);
		while (blanktest == ' ') //read AoA
		{
			blanktest = line[i];
			i++;
		}
		while (blanktest != ' ')
		{
			alphastring[strlen(alphastring)] = blanktest;
			blanktest=line[i];
			i++;
		}
			sscanf(alphastring, "%lf", &alphatest);

		if (((alpha - precision) < alphatest) && ((alpha+precision) > alphatest) && alphastring[strlen(alphastring)-1] == '0') //testing equality and last character is 0 to guarantee it is data
		{
			KeepLooping = 0;

			while (blanktest == ' ') //read CL
			{
				blanktest = line[i];
				i++;
			}	
			while (blanktest != ' ')
			{
				Clstring[strlen(Clstring)] = blanktest;
				blanktest=line[i];
				i++;
			}
			sscanf(Clstring, "%lf", Clpointer);
			//printf("at an aoa of %lf, the Cl is %lf\n", alphatest, *Clpointer);

			while (blanktest == ' ') //read Cd
			{
				blanktest = line[i];
				i++;
			}
			while (blanktest != ' ')
			{
				Cdstring[strlen(Cdstring)] = blanktest;
				blanktest=line[i];
				i++;
			}
			sscanf(Cdstring, "%lf", Cdpointer);

			while (blanktest == ' ') //read Cm
			{
				blanktest = line[i];
				i++;
			}
			while (blanktest != ' ')
			{
				blanktest=line[i];
				i++;
			}
			while (blanktest == ' ') 
			{
				blanktest = line[i];
				i++;
			}
			while (blanktest != ' ')
			{
				Cmstring[strlen(Cmstring)] = blanktest;
				blanktest=line[i];
				i++;
			}
			sscanf(Cmstring, "%lf", Cmpointer);
		}
	}
	if (feof(filepointer)) //with 3 blank lines at end of file, alphastring is 25.000 3 times until the file ends.
	{
		KeepLooping = 0;
	}
}
fclose(filepointer);
return;
}

int main(int argc, char** argv) //argc is argument count, argv is an array of space delimited argument strings
{
	double alpha = 1.25; //Initial AoA  									CHAAANNNNNGE
	double maxa = 0; //Stall maxa
	double maxcl = 0; //Stall Coeff lift
	// while(1) //Finds stall Cl
	// {
		// printf("Alpha: %g Cl: %g\n", alpha, clarkl(alpha, 0));
		// if(clarkl(alpha, 0) > maxcl)
		// {
			// maxa = alpha;
			// maxcl = clarkl(alpha, 0);
		// }
		// alpha++;
		// if(alpha > 20)
		// {
			// break;
		// }
	// }

	// printf("Max Cl is %g at alpha %g.\n", maxcl, maxa);
	// //double flap;
	double maxdist = 61; //Runway length
	double ts = .01; //Time step
	double vn = 0; //Previous velocity
	double vn1 = ts; //New velocity
	double distn = 0; //Current distance
	double tod = -1; //take off distance
	double time = 0; //Time taken
	//alpha = 0; //Reset AoA to zero
	double deflec = 4.5; //Flap deflection                       				CHAAAAAANGE
	double angv = 0; //Current angular velocity
	double angv1 = ts; //New angular velocity
	double Re = 0; //Reynolds number
	double Cl = 0;
	double Cd = 0;
	double Cm = 0;
	double* Clpointer = &Cl;
	double* Cdpointer = &Cd;
	double* Cmpointer = &Cm;
	double Cldeflec = 0;
	double Cddeflec = 0;
	double Cmdeflec = 0;
	double* Cldeflecpointer = &Cldeflec;
	double* Cddeflecpointer = &Cddeflec;
	double* Cmdeflecpointer = &Cmdeflec;
	double Cllow = 0;
	double Cdlow = 0;
	double Cmlow = 0;
	double Clhigh = 0;
	double Cdhigh = 0;
	double Cmhigh = 0;
	double Cldefleclow = 0;
	double Cddefleclow = 0;
	double Cmdefleclow = 0;
	double Cldeflechigh = 0;
	double Cddeflechigh = 0;
	double Cmdeflechigh = 0;
	double Cldefleclowangle = 0;
	double Cddefleclowangle = 0;
	double Cmdefleclowangle = 0;
	double Cldeflechighangle = 0;
	double Cddeflechighangle = 0;
	double Cmdeflechighangle = 0;

	// printf("At an aoa of %g and a Reynolds number of %g and %d degrees of deflection, the Cl is %lf, Cd is %lf, and Cm is %lf\n", alpha, Re, 0, Cl, Cd, Cm);
	// printf("At an aoa of %g and a Reynolds number of %g and %g degrees of deflection, the Cl is %lf, Cd is %lf, and Cm is %lf\n", alpha, Re, deflec, Cldeflec, Cddeflec, Cmdeflec);

	while(1)
	{
		printf("Alpha: %g, Deflec: %g\n", alpha, deflec);
		vn = vn1;
		angv = angv1;
		Re=vn1*C*RHO/MU;
		
		updatecoefficients(Re, floor(alpha), 0, Clpointer, Cdpointer, Cmpointer); //find lower bound on coefficients
		Cllow = Cl;
		Cdlow = Cd;
		Cmlow = Cm;
		updatecoefficients(Re, ceil(alpha), 0, Clpointer, Cdpointer, Cmpointer); //find upper bound on coefficients
		Clhigh = Cl;
		Cdhigh = Cd;
		Cmhigh = Cm;
		Cl = Cllow + (Clhigh-Cllow)*(alpha-floor(alpha));
		Cd = Cdlow + (Cdhigh-Cdlow)*(alpha-floor(alpha));
		Cm = Cmlow + (Cmhigh-Cmlow)*(alpha-floor(alpha));
		
		updatecoefficients(Re, floor(alpha), 5*floor(deflec/5), Cldeflecpointer, Cddeflecpointer, Cmdeflecpointer);
		Cldefleclow = Cldeflec;
		Cddefleclow = Cddeflec;
		Cmdefleclow = Cmdeflec;
		updatecoefficients(Re, ceil(alpha),  5*floor(deflec/5), Cldeflecpointer, Cddeflecpointer, Cmdeflecpointer);
		Cldeflechigh = Cldeflec;
		Cddeflechigh = Cddeflec;
		Cmdeflechigh = Cmdeflec;
		Cldefleclowangle = Cldefleclow + (Cldeflechigh-Cldefleclow)*(alpha-floor(alpha));
		Cddefleclowangle = Cddefleclow + (Cddeflechigh-Cddefleclow)*(alpha-floor(alpha));
		Cmdefleclowangle = Cmdefleclow + (Cmdeflechigh-Cmdefleclow)*(alpha-floor(alpha));
		updatecoefficients(Re, floor(alpha), 5*ceil(deflec/5), Cldeflecpointer, Cddeflecpointer, Cmdeflecpointer);
		Cldefleclow = Cldeflec;
		Cddefleclow = Cddeflec;
		Cmdefleclow = Cmdeflec;
		updatecoefficients(Re, ceil(alpha),  5*ceil(deflec/5), Cldeflecpointer, Cddeflecpointer, Cmdeflecpointer);
		Cldeflechigh = Cldeflec;
		Cddeflechigh = Cddeflec;
		Cmdeflechigh = Cmdeflec;
		Cldeflechighangle = Cldefleclow + (Cldeflechigh-Cldefleclow)*(alpha-floor(alpha));
		Cddeflechighangle = Cddefleclow + (Cddeflechigh-Cddefleclow)*(alpha-floor(alpha));
		Cmdeflechighangle = Cmdefleclow + (Cmdeflechigh-Cmdefleclow)*(alpha-floor(alpha));
		
		Cldeflec = Cldefleclowangle + (Cldeflechighangle-Cldefleclowangle)*(deflec-5*floor(deflec/5))/5;
		Cddeflec = Cddefleclowangle + (Cddeflechighangle-Cddefleclowangle)*(deflec-5*floor(deflec/5))/5;
		Cmdeflec = Cmdefleclowangle + (Cmdeflechighangle-Cmdefleclowangle)*(deflec-5*floor(deflec/5))/5;
		
		
		printf("At an aoa of %g and a Reynolds number of %g and %d degrees of deflection, the Cl is %lf, Cd is %lf, and Cm is %lf\n", alpha, Re, 0, Cl, Cd, Cm);
		printf("At an aoa of %g and a Reynolds number of %g and %g degrees of deflection, the Cl is %lf, Cd is %lf, and Cm is %lf\n", alpha, Re, deflec, Cldeflec, Cddeflec, Cmdeflec);
		double fclift = .5*RHO*pow(vn, 2)*Cl*B*C; //Calculating lift, front wing
		puts("1");
		double fcdrag = .5*RHO*pow(vn, 2)*Cd*B*C;
		puts("2");
		double rclift = .125*RHO*pow(vn, 2)*Cldeflec*B*C + .375*RHO*pow(vn, 2)*Cl*B*C; //Back wing with aileron covering 1/4 of the span
		puts("3");
		double rcdrag = .125*RHO*pow(vn, 2)*Cddeflec*B*C + .375*RHO*pow(vn, 2)*Cd*B*C;
		puts("4");
		if((2*fclift + 2*rclift) > M*G) //See if it takes off
		{
			printf("Takeoff!\n");
			break;
		}
		vn1 = ((linthrust(vn) - (2*fcdrag+2*rcdrag))/M)*ts + vn; //Numerical integral for speed
		puts("5");
		distn = distn + .5*ts*(vn1 + vn); //Numerical integral for distance
		time += ts;
		if(distn > maxdist) //If we exceed runway length, fail
		{
			printf("No takeoff.\n");
			break;
		}
		maxa = findmaxalpha(Re, alpha, 5);
		printf("plane reaches stall at %lf\n", maxa);
		deflec = pid(.01, .01, 0, maxa, alpha, ts); //Put the current state into the PID controller and set the flap deflection
		printf("new deflection is %lf, moving at a rate of %lf degrees per second\n", deflec, deflec/ts);
		puts("6");
		double fcmom = 2*C*C*B*Cm + 2*fclift*D*.5; //Moment at the front wing
		double rcmom = 0.25*2*C*C*B*Cmdeflec + 0.75*2*C*C*B*Cm + -2*rclift*D*.5; //Moment at the rear wing
		puts("7");
		// printf("front wing moment coefficient: %g\nrear wing moment coefficient: %g\n", Cm, 0.25*Cmdeflec+0.75*Cm);
		printf("Front Moment: %g\nRear Moment: %g\n", fcmom, rcmom);
		printf("%lf divided by %lf is %lf\n", (fcmom + rcmom)*ts, (M/3)*(pow(Z,2)+pow((D+2*C),2)), (fcmom + rcmom)/((M/3)*(pow(Z,2)+pow((D+2*C),2)))*ts);
		angv1 = (fcmom + rcmom)/((M/3)*(pow(Z,2)+pow((D+2*C),2)))*ts+angv; //Angular numerical velocity integral
		alpha = (alpha + (180/M_PI)*0.5*ts*(angv + angv1)); //Numerical angular position integral
		printf("the angle of attack is %lf, with the plane rotating at %lf radians per second\n", alpha, angv1);
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