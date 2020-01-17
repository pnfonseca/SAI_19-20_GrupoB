#include "mr32.h"

int disFrontdir;
int disRightdir;
int disLeftdir;
int P=0;
float speed=40;
int setpoint=700;

int
main (void)
{
  
  initPIC32 ();
  

  while (1)
    {
     
    
    
   
    readAnalogSensors();
    disRightdir=analogSensors.an7;
    disLeftdir= analogSensors.an6;

      
     // printf("AN6=%d AN7=%d \n",analogSensors.an6,analogSensors.an7);

       printf("AN6=%d AN7=%d \n", disRightdir,disLeftdir);


  if(disRightdir >= 530 || disLeftdir >= 530)
{

    if(disLeftdir <= disRightdir)
    {
      P=15;
      //speed = (float) (0.01)*(disLeftdir)*(disLeftdir);
      speed = 0.04 * disLeftdir;
    }


     if(disLeftdir > disRightdir)
    {
    P=-15;
    //speed = (float) (0.01)*(disRightdir)*(disRightdir);
    speed = 0.04 * disRightdir;
    }
}

    else if(disRightdir < 530 && disLeftdir <530 )

    {
    P=0;
    //speed = (float) (0.01)*(disFrontdir)*(disFrontdir);
    //speed = 0.6 * disFrontdir;
    speed=0;
    }

    
    setVel2(speed+P,speed-P);
    delay(200);

    //printf("disFrontdir = %d speed = %f \n", disFrontdir,speed );
    
    }

//readAnalogSensors();


  return (0);
}
