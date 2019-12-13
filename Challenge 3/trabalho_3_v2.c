#include "mr32.h"
#include <stdbool.h>
 
 
int
main (void)
{
  /* Variable declarations go here */
 
  /* initPIC32() makes all the required initializations to the
   * PIC32 hardware platform */
	initPIC32 ();
 
    TRISBbits.TRISB3 = 1;
    TRISBbits.TRISB4 = 1;
   
	bool start,stop,on;
	bool virando = false;
	int distancia_direita, distancia_esquerda, distancia_frente, valor;
	int max_distancia_frente = 25;
	

   
    enableObstSens();
    printf("A distância máxima: %d \n", max_distancia_frente);

  while (1)
    {
	
		start=PORTBbits.RB3;
		stop=PORTBbits.RB4;
		
		if (start==0){
			on=1;}
		if (stop==0){
			on=0;}
		
		while(on==1){
		readAnalogSensors();
        distancia_frente=analogSensors.obstSensFront;     
        distancia_direita=analogSensors.obstSensRight;     
        distancia_esquerda=analogSensors.obstSensLeft;		
		
		if (distancia_direita <= max_distancia_frente && !virando)
        {
            setVel2(-20,50);
			resetCoreTimer();
        }
        else if (distancia_esquerda <= max_distancia_frente && !virando)
        {
           setVel2(50,-20);
		   resetCoreTimer();
        }
        else if (distancia_frente <= max_distancia_frente)
        {
			setVel2(-50, 50);
            virando = true;
			resetCoreTimer();
        }
		else if (readCoreTimer()>100000000){
			valor=readCoreTimer();
			
			if(valor % 2 == 0){
			setVel2(-50, 50);
			wait(10);
			setVel2(80,80);
			 printf("virar para a esquerda: %d \n", max_distancia_frente);}
			
			else if (valor % 2 == 1){
			setVel2(50, -50);
			wait(10);
			setVel2(80,80);
			 printf("virar para a direita: %d \n", max_distancia_frente);}
			
			resetCoreTimer();
		}
        else
        {
            setVel2(80, 80);
            virando = false;
        }
		
		}
		
	    }
 
  return (0);
}
