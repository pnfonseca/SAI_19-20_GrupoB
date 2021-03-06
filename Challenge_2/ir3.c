#include "mr32.h"


void bin(int n)
{
 if (n > 1)
 bin(n/2);
 printf("%d", n % 2);
}



int main (void)
{
  
  initPIC32 ();
  int i=0; 
  int code=0;
  int last_pin_state;
  int pin_state ;

  last_pin_state = pin_state = PORTGbits.RG8 ; // initial state  PORTGbits.RG8

  while (1)
    {
      first: 
      
        pin_state = PORTGbits.RG8;
           if (!pin_state && last_pin_state) // pin low but was high on last read so falling edge, do something
            {
               
               resetCoreTimer();
               while(readCoreTimer() <= 54000)  //means <= 2500us  clk cpu=20*10^6
               {
                   last_pin_state = pin_state; 
                   pin_state = PORTGbits.RG8;
                   if (!pin_state && last_pin_state) // pin low but was high on last read so falling edge, do something 
                     
                   goto first;
               } 

               code = 0;
               
               
               nextbit: 
               delay(12);//1200us first bit 
               if(PORTGbits.RG8==1) //means this bit was 0
               {
                   code=code | 1 ; 
                    i++;           
               }  goto nextbit;             
                               
               if(PORTGbits.RG8==0) //means this bit was 1 
               {   
                  code=code & (0xFF-0x01) ;
                  i++;
                   delay(600);
               } 
               if(i==12) 
               {
               printf("code= "); 
               bin(code);
               printf(" \n "); 
               last_pin_state = pin_state;
               i=0;
               goto first;
               }
               else goto nextbit;





               
               
               
               

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
