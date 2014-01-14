#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main ()
{
int i = 0;
float aoa; 					//angle of attack
float aoatest;
float Re;  					//Reynolds number
char file_name[25] = ""; 	//initializing filename with an empty string
char blanktest = ' ';					//testing for blanks when reading file
char Restring[25];			//variable that will hold Reynolds number as a string
char Restringtrunc[25]; 	//Reynolds number rounded to nearest 5000
char aoastring[25];			//angle of attack string
int Reincrement = 5000; 
char line[100];				//string to hold line of file
double Cl;
double Cd;
char Clstring[25];
char Cdstring[25];
int KeepLooping = 1;
FILE *filepointer;

scanf("%f %g", &aoa, &Re);
strcat(file_name, "./s1223rawdata/S1223_T1_Re"); 			//1st part of filename
Re = floor(Re/Reincrement)*Reincrement; 					//rounding to nearest 5000
sprintf(Restring, "%f", Re/1000000); 						//converting to string
strncpy(Restringtrunc, Restring, 5);						//truncating to 5 digits
Restringtrunc[5] = '\0'; 									//adding 0 to make it a string
strcat(file_name, Restringtrunc); 							//adding 2nd part of filename
strcat(file_name, "_M0.00_N9.0.txt "); 						//adding last part of filename
printf("%s", file_name);	


filepointer = fopen(file_name, "r"); //read mode
if (filepointer == NULL)
{
	perror("Error while opening the file.\n");
	exit(EXIT_FAILURE);
}

while(1 && KeepLooping)			
{
	i = 0;
	fgets(line, 100, filepointer);
	
	while (blanktest == ' ') //read AoA
	{
		blanktest = line[i];
		i++;
	}
	while (blanktest != ' ')
	{
		aoastring[strlen(aoastring)] = blanktest;
		//strcat(aoastring, blanktest);
		blanktest=line[i];
		i++;
	}
		sscanf(aoastring, "%f", &aoatest);
	
	if (aoa == aoatest)
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
			//strcat(Clstring, blanktest);
			blanktest=line[i];
		}
		sscanf(Clstring, "%lf", &Cl);
	
		while (blanktest == ' ') //read Cd
		{
			blanktest = line[i];
			i++;
		}
		while (blanktest != ' ')
		{
		Cdstring[strlen(Cdstring)] = blanktest;
		//strcat(Cdstring, blanktest);
		blanktest=line[i];
		}
		sscanf(Cdstring, "%lf", &Cd);
	}
}
//until " " character is not met
//read characters until " " character is met
//if string size is above 1, to avoid line 5 in file
//store in variable
//convert to double
//if double is equal to AoA, read other coefficients
//if not, go to next line
return 0;
}
