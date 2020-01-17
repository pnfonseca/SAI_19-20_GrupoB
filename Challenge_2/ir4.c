#include "mr32.h"


void printbit(int n)
{
 if (n > 1)
 printbit(n/2);
 printf("%d", n % 2);
}

unsigned int pow2[] = {1,2,4,8,16,32,64,128,256,512,1024,2048,4096};

int main (void)
{
  
  initPIC32 ();
  int i=0; 
  int code=0;
  int last_pin_state;
  int pin_state ;
  int bitnumber=12;
  last_pin_state = pin_state = PORTGbits.RG8 ; // initial state  PORTGbits.RG8
  int nosignal=1;
  int speed=50;
  unsigned long count=0;

  while (1)
    {
      first: 
      count++;
      if(count>100000) 
        { setVel2(0,0);  speed=0;  }
     
     pin_state = PORTGbits.RG8;
     if (!pin_state && last_pin_state) // pin low but was high on last read so falling edge, do something
        {
               
           resetCoreTimer();
           while(readCoreTimer() < 42000)  //means <= 2100us  clk cpu=20*10^6
            {
              if(PORTGbits.RG8==1)
              goto first;
            } 

            delay(6); //600us first bit 
            
            count=0;
            speed = 50;

            for (i=0 ; i < bitnumber ; i++)   
            {  
               delay(12);//1200us first bit 

               if(PORTGbits.RG8==1) //means this bit was 0
               {
                code=code & (0xFF-pow2[i]) ; 
                
               }  
                               
               if(PORTGbits.RG8==0) //means this bit was 1 
               {   
                code=code | pow2[i] ;
                
                delay(6);//600us first bit 
               } 
                
               if(i==bitnumber-1) 
               {
               printf("code= "); 
               printbit(code);
               printf(" \n "); 
               printf("code= %d\n",code); 
               
                if(code==2176)//means No1 
                setVel2(speed/2,speed);
                if(code==2177)//means No2 
                setVel2(speed,speed);
                if(code==2178)//means No3 
                setVel2(speed,speed/2);
                if(code==2179)//means No4
                setVel2(-speed,speed);
                if(code==2181)//means No6
                setVel2(speed,-speed);
                if(code==2183)//means No8
                setVel2(-speed,-speed);
                if(code==2180)//means No5
                setVel2(0,0);
                




               }
            }  
        }
        last_pin_state = pin_state;
    }
  return (0);
}
