#include "mr32.h"

void bin(int n)

{
   
 /* Step 1 */
     
if (n > 1)
       
 bin(n/2);
    
/* Step 2 */
   
 printf("%d", n % 2);

}



int main (void)
{
  
  initPIC32 ();
  int code=0;
  int last_pin_state;
  int pin_state ;

  last_pin_state = pin_state = PORTGbits.RG8 ; // initial state  PORTGbits.RG8

  while (1)
    {
      first: 
      //LATEbits.LATE0=0;
      //LATEbits.LATE1=0;
      //LATEbits.LATE2=0;

           pin_state = PORTGbits.RG8;
           if (!pin_state && last_pin_state) // pin low but was high on last read so falling edge, do something
            {               
               resetCoreTimer();
               while(readCoreTimer() <= 40000)  //means <= 2500us  clk cpu=20*10^6
               {
                 
                   //last_pin_state = pin_state;
                   pin_state = PORTGbits.RG8;
                   //if (!pin_state && last_pin_state) // pin low but was high on last read so falling edge, do something 
                   if (pin_state)
                       goto first;
                   //last_pin_state = pin_state;                       
               } 

               code = 0;

               delay(9);//900us first bit 
               if (PORTGbits.RG8==0) code=code & (0xFF-0x01) ; 
                               else  code=code | 1 ;

               delay(9);//900us second bit
               if (PORTGbits.RG8==0) code = code & (0xFF-0x02);
                               else  code = code | 2; 

               delay(9);//900us third bit
               if (PORTGbits.RG8==0) code = code & (0xFF-0x04);
                               else  code = code | 4;       
               //delay(300);

               printf("code= "); 
               bin(code);
               printf(" \n "); 
               
               
               //LATEbits.LATE0=1;

               if(code==4)
               {
               LATEbits.LATE0=1;
               LATEbits.LATE1=0;
               LATEbits.LATE2=0;
               setVel2(0,15);
               }
               if(code==2)
               {
               LATEbits.LATE0=0;
               LATEbits.LATE1=1;
               LATEbits.LATE2=0;
               setVel2(50,50);
               }
               if(code==0)
               {
               LATEbits.LATE0=0;
               LATEbits.LATE1=0;
               LATEbits.LATE2=1;
               setVel2(15,0);
               }
            
                goto first;
               

            }
            last_pin_state = pin_state;
         
     }
  return (0);
}
