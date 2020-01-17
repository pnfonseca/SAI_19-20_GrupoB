#include "mr32.h"


int last_pin_state;
int pin_state ;
int edgeflag;
int time=0;
int num=1;

int main (void)
{
 
  initPIC32 ();
  last_pin_state = pin_state = PORTGbits.RG8 ;


  while (1)
    {
      last_pin_state = pin_state ;
      pin_state = PORTGbits.RG8 ;
      

      //if (!pin_state && last_pin_state)
      if (PORTGbits.RG8 ==0)
      {
          edgeflag =1;
          resetCoreTimer();
          //edgeflag=1;
          while(PORTGbits.RG8==0) ;
      }
      //last_pin_state =PORTGbits.RG8;
      
      time = readCoreTimer();
        //if(edgeflag==1)  
        //{
            if (time>1000&& edgeflag )
            {
                printf("time= %d \n ", time );
                delay(20000);
                edgeflag=0;      
            }
        //}

    }

    
  return 0;
}
