#include "mr32.h"

//Variable corresponding to the distance of the front sensor.
int disFrontdir;
//Variable corresponding to the distance of the right sensor.
int disRightdir;
//Variable corresponding to the distance of the left sensor.
int disLeftdir;

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
    
	//Printing the value provided by each sensor.
    printf("disleftdir = %d   ",disLeftdir);
    printf("disfrontdir= %d   ",disFrontdir);
    printf("disrightdir= %d\n ",disRightdir);

	//Copy/Save the value provided by the obstacle sensors.
    disFrontdir=obstacleSensor(OBST_SENSOR_FRONT);
    disRightdir=obstacleSensor(OBST_SENSOR_RIGHT);
    disLeftdir=obstacleSensor(OBST_SENSOR_LEFT);

	//Verifying if distance between robot and obstacle (detected by front sensor) is less than 30 and if value provided by left sensor is less or equal to value provided by right sensor.
    if(disFrontdir < 30 && (disLeftdir <= disRightdir)) setVel2(40,0);

	//Verifying if distance between robot and obstacle (detected by front sensor) is less than 30 and if value provided by left sensor is bigger the value provided by right sensor.
    else if(disFrontdir < 30 && (disLeftdir > disRightdir)) setVel2(0,40);

	//Verifying if distance between robot and obstacle (detected by left sensor) is less than 30.
    else if(disLeftdir < 30) setVel2(40,0);
    
	//Verifying if distance between robot and obstacle (detected by right sensor) is less than 30.
    else if(disRightdir < 30) setVel2(0,40);
    
	//Setting the robot speed.
    else setVel2(40,40);

    }
  return (0);
}
