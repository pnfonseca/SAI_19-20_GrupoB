#include "mr32.h"

int
main (void)
{
  
  unsigned int value;
  unsigned int readLineSensors(int gain);
  int start;
    
  initPIC32 ();
  disableGroundSens();
  printf("%s\n",__DATE__);
  printf("%s\n",__TIME__);
   
  while (1)
    {
      /* Code goes here */
      if (PORTBbits.RB3==0)
		{
			LATEbits.LATE0 = 1;
		}
	  else 
		{
			LATEbits.LATE0 = 0;
		}
		
		if (PORTBbits.RB3 == 0 && readLineSensors(0) == 31)
			{
				start = 1;
			}
			
		printf("%d\r",readLineSensors(0));

		while (start == 1)
    {
		printf("START = OK");
	    enableGroundSens();
		wait(1);
		readLineSensors(0);
		value =readLineSensors (0);
		printf("%d\r",value);
		wait(5);
		disableGroundSens();
		wait(5);
		
		if (PORTBbits.RB4 == 0)
		{
			start = 0;
		}
	}
  } 
    
  return (0);
}
