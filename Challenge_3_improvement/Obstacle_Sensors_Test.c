#include "mr32.h"

//Variable corresponding to the distance of the front sensor.
int disFrontdir;
//Variable corresponding to the distance of the right sensor.
int disRightdir;
//Variable corresponding to the distance of the left sensor.
int disLeftdir;

int
main (void)
{
	
  //Library.
  initPIC32 ();
  
  while (1)
    {
    
	//Activation of obstacle sensors.
    enableObstSens();
	//Start reading analog sensors.
    readAnalogSensors();
	
	//Copy/Save the value provided by the obstacle sensors.
    disFrontdir=obstacleSensor(OBST_SENSOR_FRONT);
    disRightdir=obstacleSensor(OBST_SENSOR_RIGHT);
    disLeftdir=obstacleSensor(OBST_SENSOR_LEFT);
    
	//Printing the value provided by each sensor.
    printf("disleftdir = %d   ",disLeftdir);
    printf("disfrontdir= %d   ",disFrontdir);
    printf("disrightdir= %d\n ",disRightdir);
	
    }
  return (0);
}
