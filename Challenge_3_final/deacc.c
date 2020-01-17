#include "mr32.h"
#include <math.h>

//Variable corresponding to the distance of the front sensor.
float disFrontdir;
//Variable corresponding to the robot speed.
float speed;
//Variable corresponding to average value of distance between robot and obstacle.
float avg=0;
//Variable used in cicle 'For'.
int i=0;

int
main (void)
{
	
  //Library.
  initPIC32 ();

  //Robot default initial speed setting.
  setVel2(10,10);
  delay(10000);
  //Robot default speed setting.
  setVel2(20,20);
  delay(10000);

  while (1)
    {
     
	//To consider the encoders behind the motors.
    closedLoopControl (true);
	
	//Activation of obstacle sensors.
    enableObstSens();

	//Setting the 'AVG' variable default value to 0.
    avg=0;
	//Cicle used to eliminate the flutuation of value returned by obstacle sensor/sensors.
    for(i=0 ; i<50 ; i++)
    {
	//Start reading analog sensors.
    readAnalogSensors();
    delay(10);
	//Copy/Save the value provided by the front sensor.
    disFrontdir=obstacleSensor(OBST_SENSOR_FRONT);
	//First part of averaging. Sum of 50 values provided by front sensor.
    avg = avg + disFrontdir;
    }
	
	//Second part of averaging. Division of AVG sum result by number of read values. Subtraction of number '12' to get zero at the minimum distance between robot and obstacle.
    disFrontdir=(int) (0.02 * avg) - (12);

	//Printing the value provided by front sensor.
    printf("disfrontdir= %f   ",disFrontdir);

	//Definition of speed through a function of type 'y=x^2'.
    speed = (float) (0.3) * (disFrontdir) * (disFrontdir);
    
	//Verifying if speed is bigger then '50'.
    if (speed > 50) speed=50;
	
	//Verifying if value provided by front sensor is less or equal to zero.
    if (disFrontdir <= 0) speed=0;
	
	//Setting the robot speed.
    setVel2(speed,speed);
    
	//Printing the value of speed.
    printf("speed = %f\n  ",speed);

}
  return (0);
}
