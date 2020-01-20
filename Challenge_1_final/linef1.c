#include "mr32.h"

#define maxspeed 0

#define REDBOTTON PORTBbits.RB3
#define BLACKBOTTON PORTBbits.RB4

// define varable speed at 60
int speed=60;
// define counter = 0
int count=0;
// define flag = 0 to reset the sequence when it is = to 15
int Flag=0;
//define just for test
int Cycle=0;
//define variable distance as 0 
unsigned int Distance=0;

int main (void)
{
//index of for 
int i;
//temporary variable
int avg;
//initialize microcontroler register
initPIC32 ();
//Set speed of both motors to 30%
setVel2(30,30);
//Anable Ground Sensors
enableGroundSens();
//Anable obstacle sensors
enableObstSens();
	
while (1)
	{
	//Increase general speed if Red button is pressed and speed < 100
    if(REDBOTTON==0 && speed<100)
        speed=speed+1;
	//Decrease general speed if Black button is pressed and speed > 0
    if(BLACKBOTTON==0 && speed>0)
        speed=speed-1;  
     
    //Read All sensors
	unsigned int a = readLineSensors(0);
	//Read each sensor one by one
	unsigned int Right2 =  a & 0x01;
	unsigned int Right1 = (a & 0x02)>>1;
	unsigned int Center = (a & 0x04)>>2;
	unsigned int Left1  = (a & 0x08)>>3;
	unsigned int Left2  = (a & 0x16)>>4;
     
	//when robot sence the start line
	if(a==0x1F)
		{
		Flag=1;
		}
	// when robot pass the start line
	if(Flag==1 && a!=0x1F)
		{
		count++;  
		Flag=0;
		}
	//Lightning the 4 leds with binary code in each lap
	LATEbits.LATE0=  count & 0x01;
	LATEbits.LATE1= (count & 0x02)>>1;
	LATEbits.LATE2= (count & 0x04)>>2;
	LATEbits.LATE3= (count & 0x08)>>3;

	//Go forward if robot sence middle sensor
	if(Center)
		setVel2(speed,speed);
	//Turns slightly to the right if robot sense sensor right1
	else if(Right1)
		setVel2(speed,speed/3);
		//Turns slightly to the left if robot sense sensor left1
	else if(Left1) 
		setVel2(speed/3,speed);
	//Turns completly to the right if robot sense sensor right2
	else if(Right2)
		{
		do
			{
			setVel2(speed,0);
			}while(Center);
		}
	//Turns completly to the left if robot sense sensor left2
	else if(Left2)
		{
		do
			{
			setVel2(0,speed);
			}while(Center);
		}

 
	//read sensors
	readAnalogSensors();
	//get distance of front obstacle sensor
	Distance=obstacleSensor(OBST_SENSOR_FRONT);
	//Stop Robot while Distance < 30
	while (Distance<=30)
		{
		setVel2(0,0);
		readAnalogSensors();                          //read obstacle sensors and
		delay(10);                                    //delay cause of limitation of sample rate in analog sensor
		avg =0;
		for (i=0;i<50;i++)                            //get average cause of oscilating the value of sensor
			avg += obstacleSensor(OBST_SENSOR_FRONT);
		
		Distance = (int)(avg/50);
		printf("d =%d C1=%d\n",Distance,Cycle);
		}
	 
	printf("d =%d C=%d\n",Distance,Cycle);
   
   
	}
  return (0);
}