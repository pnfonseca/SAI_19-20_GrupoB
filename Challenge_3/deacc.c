#include "mr32.h"
#include <math.h>

float disFrontdir;
int disRightdir;
int disLeftdir;
float speed;
float avg=0;
int i=0;


int
main (void)
{
  
  initPIC32 ();

setVel2(10,10);
delay(10000);
setVel2(20,20);
delay(10000);

  while (1)
    {
     
    closedLoopControl( true );

    enableObstSens();

    avg=0;
    for(i=0 ; i<50 ; i++)
    {
    readAnalogSensors();
    delay(10);
    disFrontdir=obstacleSensor(OBST_SENSOR_FRONT);
    avg=avg+disFrontdir;
    }
    disFrontdir=(int) (0.02*avg)-(12) ;

    printf("disfrontdir= %f   ",disFrontdir);

    speed = (float) (0.3)*(disFrontdir)*(disFrontdir);
    
    if(speed>50) speed=50;
    if(disFrontdir <= 0) speed=0;
    //speed = 800*speed;
    setVel2(speed,speed);
    
   
    printf("speed = %f\n  ",speed);

}
  return (0);
}
