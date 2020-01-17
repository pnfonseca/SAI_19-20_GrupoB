#include "mr32.h"

int disFrontdir;
int disRightdir;
int disLeftdir;

int
main (void)
{
  
  initPIC32 ();
  

  while (1)
    {
     
    
    enableObstSens(); 
    readAnalogSensors();
    
    //disrightdir=obstacleSensor(OBST_SENSOR_RIGHT);
    
    //
    
    printf("disleftdir = %d   ",disLeftdir);
    printf("disfrontdir= %d   ",disFrontdir);
    printf("disrightdir= %d\n ",disRightdir);
    

    disFrontdir=obstacleSensor(OBST_SENSOR_FRONT);
    disRightdir=obstacleSensor(OBST_SENSOR_RIGHT);
    disLeftdir=obstacleSensor(OBST_SENSOR_LEFT);

   /*
    while (disFrontdir< 40 && (disLeftdir <40)) 
    {
      readAnalogSensors();
      disFrontdir=obstacleSensor(OBST_SENSOR_FRONT);
      disRightdir=obstacleSensor(OBST_SENSOR_RIGHT);
      disLeftdir=obstacleSensor(OBST_SENSOR_LEFT);
      setVel2(20,-30);
      delay(2000);
    }

    while (disFrontdir< 40 && (disRightdir < 40)) 
    {
      readAnalogSensors();
      disFrontdir=obstacleSensor(OBST_SENSOR_FRONT);
      disRightdir=obstacleSensor(OBST_SENSOR_RIGHT);
      disLeftdir=obstacleSensor(OBST_SENSOR_LEFT);
      setVel2(-30,20);
      delay(2000);
    }
*/
    if(disFrontdir< 30 && (disLeftdir <= disRightdir)) setVel2(40,0);

    else if(disFrontdir< 30 && (disLeftdir > disRightdir)) setVel2(0,40);

    else if(disLeftdir< 30) setVel2(40,0);
    
    else if(disRightdir< 30) setVel2(0,40);
    
    else setVel2(40,40);

/*
    if(disLeftdir <= disRightdir) 
    {
    setVel2(40,0);
    delay(5000);
    }
    else if(disLeftdir > disRightdir) 
    {
    setVel2(0,40);
    delay(5000);
    }
   // else if(disLeftdir< 30) setVel2(40,0);
    
   // else if(disRightdir< 30) setVel2(0,40);
    
    else 
    {
    setVel2(40,40);
    delay(5000);
    } */



    }
  return (0);
}
