#include "mr32.h"

//Variable corresponding to the distance of the front sensor.
int disFrontdir;

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
	
    //Printing the value provided by Front sensor.
    printf("disfrontdir= %d   ",disFrontdir);

	//Copy/Save the value provided by Front sensor.
    disFrontdir=obstacleSensor(OBST_SENSOR_FRONT);

	//Verifying if distance between robot and obstacle (detected by front sensor) is less than 30 (default value).
    if(disFrontdir <= 30)
	{
		
		//Robot stops, to avoid the colision with the obstacle.
		setVel2(0,0);
		//Delay time.
		delay(200);
		//Robot rotates around the axis of your wheel, to avoid the obstacle.
		setVel2(40,0);
		//Delay time.
		delay(200);
		//Robot resumes its movement.
		setVel2(40,40);
		
	}
	
    //Setting the robot speed.
    else setVel2(40,40);

    }
  return (0);
}
