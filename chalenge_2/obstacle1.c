#include "mr32.h"

int disfrontdir;
int disrightdir;
int disleftdir;

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
    
    printf("disleftdir = %d   ",disleftdir);
    printf("disfrontdir= %d   ",disfrontdir);
    printf("disrightdir= %d\n ",disrightdir);
    
    disfrontdir=obstacleSensor(OBST_SENSOR_FRONT);
    disrightdir=obstacleSensor(OBST_SENSOR_RIGHT);
    disleftdir=obstacleSensor(OBST_SENSOR_LEFT);

    if(disfrontdir< 30 && (disleftdir < disrightdir)) setVel2(0,40);

    else if(disfrontdir< 30 && (disleftdir < disrightdir)) setVel2(40,0);

    //else if(disleftdir< 30) setVel2(40,0);

    
    //else if(disrightdir< 30) setVel2(0,40);
    
    else setVel2(40,40);






    }
  return (0);
}
