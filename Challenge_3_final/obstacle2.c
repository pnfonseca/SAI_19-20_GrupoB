#include "mr32.h"

//Variable corresponding to the distance of the front sensor.
int disFrontdir;
//Variable corresponding to the distance of the right sensor.
int disRightdir;
//Variable corresponding to the distance of the left sensor.
int disLeftdir;
//Variable to define the robot rotation direction (default value 0).
int P=0;
//Default speed.
float speed=40;
//Variável corresponding to minimum acceptable distance between the robot and obstacle.
int setpoint=30;

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
  
	//Verifying if distance between robot and obstacle (detected by front sensor) is less than minimum acceptable distance and if value provided by left sensor is less or equal to value provided by right sensor.
    if(disFrontdir < setpoint && (disLeftdir <= disRightdir)) 
    {
		//Setting the value of variable 'P' to 7.
		P=7;
		//Robot speed setting, according to the distance of the left sensor.
		speed = 0.6 * disLeftdir;
    }
	
	//Verifying if distance between robot and obstacle (detected by front sensor) is less than minimum acceptable distance and if value provided by left sensor is bigger the value provided by right sensor.
    else if(disFrontdir < setpoint && (disLeftdir > disRightdir)) 
    {
		//Setting the value of variable 'P' to -7.
		P=-7;
		//Robot speed setting, according to the distance of the right sensor.
		speed = 0.6 * disRightdir;
    }
	
	//Verifying if distance between robot and obstacle (detected by right sensor) and if value provided by left sensor is bigger than minimum acceptable distance.
    else if(disRightdir > setpoint && disLeftdir > setpoint )
    {
		//Setting the value of variable 'P' to 0.
		P=0;
		//Robot speed setting, according to the distance of the front sensor.
		speed = 0.6 * disFrontdir;
    }
    
	//Setting the robot speed. The 'P' variable determines the motion direction of the robot.
    setVel2(speed+P,speed-P);
    delay(200);

	//Printing the value provided by each sensor and the robot velocity.
    printf("disFrontdir = %d speed = %f \n", disFrontdir,speed);
    printf("disRightdir = %d speed = %f \n", disRightdir,speed);
    printf("disLeftdir = %d speed = %f \n", disLeftdir,speed);
    
    }
  return (0);
}
