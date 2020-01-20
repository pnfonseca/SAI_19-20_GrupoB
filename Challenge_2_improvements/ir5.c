#include "mr32.h"

//---------------------------------------------------printbit()------------------------------------------------

void printbit(int n)
{
 if (n > 1)
 printbit(n/2);
 printf("%d", n % 2);
}

//------------------------------------------------------main()------------------------------------------//

unsigned int pow2[] = {1,2,4,8,16,32,64,128,256,512,1024,2048,4096};

int main(void)
{
  
  int i=0; 
  int code=0;
  int last_pin_state;
  int pin_state ;
  int bitnumber=12;
  last_pin_state = pin_state = PORTGbits.RG8 ; // initial state  PORTGbits.RG8
  int nosignal=1;
  int speed=50;
  int j=0;

  while (1)
    {
      first: 
      j++;
           
      pin_state = PORTGbits.RG8;                                // read the port and put it in pin_state 
      if (!pin_state && last_pin_state)                         // pin is low but was high on last read it means falling edge
        {
           resetCoreTimer();                                    //reset counter
                                                                //find Start of packet data
           while(readCoreTimer() < 42000)                       //means <= 2100us  clk cpu=20*10^6
           {
            if(PORTGbits.RG8==1)                              
            goto first;
           } 

            delay(6);                                           //Pass the start of packet , delay(6)= 600us 

           for (i=0 ; i < bitnumber ; i++)                      //start to read 12 bit
           {  
            delay(12);                                          //1200us first bit 
    
            if(PORTGbits.RG8==1)                                //means this bit was 0
            code=code & (0xFF-pow2[i]) ; 
                 
            if(PORTGbits.RG8==0)                                //means this bit was 1 
            {   
             code=code | pow2[i] ;
             delay(6);                                          //600us first bit 
            } 
                
            if(i==bitnumber-1) 
            {
             printf("code= "); 
             printbit(code);
             printf(" \n "); 
               
             delay(10000);
            }
        }  
    }
     last_pin_state = pin_state;
    }
  return (0);
}
