#include "mr32.h"

int
main (void)
{

  initPIC32 ();

  while (1)
    {

      readAnalogSensors();

      printf("AN6=%d AN7=%d \n",analogSensors.an6,analogSensors.an7);

delay(5000);


    }
  return (0);
}

