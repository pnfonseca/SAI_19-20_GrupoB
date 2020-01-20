#include "mr32.h"
#include <math.h>
#include <stdlib.h>

// Variables
int disRightdir; // photodiode pointing to right value
int disLeftdir; // photodiode pointing to left value
int P=0;
float speed=40;
int dif_values;

int
main (void)
{
  initPIC32 ();

  while (1)
    { 

		readAnalogSensors(); //PIC32 function to update inputs
		disRightdir = analogSensors.an7;
		disLeftdir = analogSensors.an6;     
		
		//print current values from each photodiode
		printf("AN6=%d AN7=%d \n", disRightdir,disLeftdir);
		
		
		//set minimum values of light to make the robot move. Value = x ---> | right diode value = > x __OR___ left diode value = > x |
		if(disRightdir >= 540 || disLeftdir >= 540)
		{
			//absolute diference between the diode values
			dif_values = abs(disRightdir - disLeftdir);
			// if the diode pointing right has an higher value,turn right
			if((disLeftdir <= disRightdir) && (dif_values > 50))
			{				
				P=15;
				speed = 0.04 * disRightdir;
				setVel2(speed-P,speed+P);
				delay(200);				
			}
			// if the diode pointing right has an higher value,turn right
			else if((disLeftdir > disRightdir)  && (dif_values > 50))
			{
				P=-15;
				speed = 0.04 * disLeftdir;
				setVel2(speed-P,speed+P);
				delay(200);
			}
			// if the diference between the diode values is small enought, it means the light most certainly comes from the front
			else if (dif_values < 50)
			{	
				P = 0;
				speed = 0.04 * disLeftdir;
				setVel2(speed-P,speed+P);
				delay(200);
			}
			// if no condiction is TRUE, rotate till find the light source
			else
			{
				setVel2(-10,10);
				delay(200);
			}
		}
		//if the values from both sensors are below the setpoint, stop the robot
		else
		{
			setVel2(-10,10);
			delay(200);
		}
    
    }
	
  return (0);
}