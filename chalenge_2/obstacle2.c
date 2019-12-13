#include "mr32.h"

int disFrontdir;
int disRightdir;
int disLeftdir;
int P=0;
float speed=40;
int setpoint=30;

int
main (void)
{
  
  initPIC32 ();
  

  while (1)
    {
     
    
    enableObstSens(); 
    readAnalogSensors();
    
   
    disFrontdir=obstacleSensor(OBST_SENSOR_FRONT);
    disRightdir=obstacleSensor(OBST_SENSOR_RIGHT);
    disLeftdir=obstacleSensor(OBST_SENSOR_LEFT);

  
    if(disFrontdir< setpoint && (disLeftdir <= disRightdir)) 
    {
      P=7;
      //speed = (float) (0.01)*(disLeftdir)*(disLeftdir);
      speed = 0.6 * disLeftdir;
    }


    else if(disFrontdir< setpoint && (disLeftdir > disRightdir)) 
    {
    P=-7;
    //speed = (float) (0.01)*(disRightdir)*(disRightdir);
    speed = 0.6 * disRightdir;
    }


    else if(disRightdir >setpoint && disLeftdir >setpoint )

    {
    P=0;
    //speed = (float) (0.01)*(disFrontdir)*(disFrontdir);
    speed = 0.6 * disFrontdir;
    }

    
    setVel2(speed+P,speed-P);
    delay(200);

    printf("disFrontdir = %d speed = %f \n", disFrontdir,speed );
    
    }
  return (0);
}
