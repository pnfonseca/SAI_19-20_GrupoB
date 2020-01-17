#include "mr32.h"

#define maxspeed 0

#define REDBOTTON PORTBbits.RB3
#define BLACKBOTTON PORTBbits.RB4

int speed=60;
int count=0;
int Flag=0;
int Cycle=0;
unsigned int Distance=0;

int main (void)
{
  int i,d;
initPIC32 ();                       // makes all the required initializations to the
setVel2(30,30);

enableGroundSens();
enableObstSens();

  while (1)
    {

     if(REDBOTTON==0 && speed<100)
         speed=speed+1;
     
     if(BLACKBOTTON==0 && speed>0)
         speed=speed-1;  

     
     
     unsigned int a = readLineSensors(0);

     unsigned int Right2 =  a & 0x01;
     unsigned int Right1 = (a & 0x02)>>1;
     unsigned int Center = (a & 0x04)>>2;
     unsigned int Left1  = (a & 0x08)>>3;
     unsigned int Left2  = (a & 0x10)>>4;
     
 
     if(a==0x1F)
     {
       Flag=1;
     }

     if(Flag==1 && a!=0x1F)
     {
        count++;  
        Flag=0;
     }

     LATEbits.LATE0=  count & 0x01;
     LATEbits.LATE1= (count & 0x02)>>1;
     LATEbits.LATE2= (count & 0x04)>>2;
     LATEbits.LATE3= (count & 0x08)>>3;

       // disableGroundSens();

     
        if(Center)
	      setVel2(speed,speed);
            else if(Right1)
                setVel2(speed,speed/3);
                    else if(Left1) 
                    setVel2(speed/3,speed);
	                else if(Right2)
		                {
                   do
                    {
                    setVel2(speed,0);
            }while(Center);
            }
	        else if(Left2)
	        {
            do
            {
          setVel2(0,speed);
            }while(Center);
	  }
  
   
   
	}
  return (0);
}