#include "mr32.h"

//---------------------------------------------------printbit()----------------------------------------------//

void printbit(int n)
{
 if (n > 1)
 printbit(n/2);
 printf("%d", n % 2);
}

//------------------------------------------------------main()-----------------------------------------------//

unsigned int pow2[] = {1,2,4,8,16,32,64,128,256,512,1024,2048,4096};

int main(void)
{
  initPIC32 ();
  int i=0;                                                    //index of "for"
  int code=0;                                                 //remote code
  
  int last_pin_state;                                         //temporary parameter for keeping last state  
  int pin_state ;                                             //parameter for keeping curent state

  int bitnumber=12;                                           //number of bits command packet
  int startpacket =1;                                         //flag shows the start of packet
  int speed=40;                                               //set speed to robot
    
  last_pin_state = pin_state = PORTGbits.RG8 ;                //initial state  PORTGbits.RG8

  while (1)
    {
        
        pin_state = PORTGbits.RG8;                            // read the port and put it in pin_state 
        if (!pin_state && last_pin_state)                     // pin is low but was high on last read it means falling edge
        {
                resetCoreTimer();                             //reset counter
                                                              //find Start of packet data
                while(readCoreTimer() < 42000)                //means <= 2100us  clk cpu=20*10^6
                {                    
                    if(PORTGbits.RG8==1)                              
                    {
                        startpacket = 0;
                        break;
                    }
                } 

                if (startpacket)                              //if find start of command
                {
                    delay(6);                                 //Pass the start of packet , delay(6)= 600us 

                    for (i=0 ; i < bitnumber ; i++)           //start to read 12 bit
                    {  
                            delay(12);                        //1200us first bit 
                    
                            if(PORTGbits.RG8==1)              //means this bit was 0
                                code=code & (0xFF-pow2[i]) ;  //set bit(i)=0
                                
                            if(PORTGbits.RG8==0)              //means this bit was 1 
                            {   
                                code=code | pow2[i] ;         //set bit(i)=1
                                delay(6);                     //600us delay to get ready for reading next bit 
                            } 
                                
                            if(i==bitnumber-1) 
                            {
                                printf("code= "); 
                                printbit(code);               //Print binary
                                printf(" \n "); 

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
        }
    last_pin_state = pin_state;                                //Remember last pin_state 
    }
  return (0);
}
