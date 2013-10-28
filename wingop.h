#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define M_PI 3.14159265358979323846
#define RHO 1.225 //ISA standard
#define G 9.81 //Standard gravity
#define CR 0.03 //Knicked from Florida
#define MDEM 4.445 //Max len + width + height
#define FUSEW .13 //Fuse width
#define ENGL .12 //Engine length
#define LANDH .2 //Landing gear height
#define FUSECD .82 //Long cylinder.
#define E 0.7 // efficiency for square wings
#define CF 0.006297 //Skin friction coeff
#define MU .00001796
#define AC .256

extern double V;
extern double A1;
extern double A2;
extern double C1;
extern double C2;
extern double B1;
extern double B2;
extern double D;
extern double Z;
extern double L1;
extern double L2;
extern double S1;
extern double S2;
extern double AR1;
extern double AR2;

void ldairfoil();
double drag(double c1, double c2, double a1, double a2, double s1, double s2, double ar1, double ar2, double l1, double l2, double v);
double lift(double s, double a, double v, double c);
double thrust(double v);
double takeoffd(double a1, double a2, double c1, double c2, double b1, double b2, double d, double z, double m, double step);
double s1223cl(double a, double v, double l);
double s1223cd(double a, double v, double l);
double s1223cm(double a, double v, double l);
char checkstab(double a1, double a2, double c1, double c2, double b1, double b2, double d, double z);
