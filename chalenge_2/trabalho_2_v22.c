#include "mr32.h"
#include <stdbool.h>
#include <string.h>

#define SIZE	33

int
main (void)
{
  /* Variable declarations go here */

  /* initPIC32() makes all the required initializations to the
   * PIC32 hardware platform */
  initPIC32 ();

	TRISEbits.TRISE0 = 0;
	TRISEbits.TRISE1 = 0;

	TRISBbits.TRISB3 = 1;
	TRISBbits.TRISB4 = 1;
	
	TRISGbits.TRISG7 = 1;
	
bool start,stop;
int bit_lido, escutar, contagem_bit, espera,i;
char leituras[SIZE];

char desligar[SIZE]="00001100011100001111111111111111";	
char frente[SIZE]=  "00000011000100000111111111111111"; 
char tras[SIZE]=    "00001100010001101011111111111111"; 
char peao[SIZE]=    "00001100000100000111111111111111";
char direita[SIZE]=    "00001000001100000111111111111111"; 
char esquerda[SIZE]=    "00000011000011101111111111111111";

escutar=0;
contagem_bit=0;
espera=0;
printf("acordei");
printf( "\n" );



  while (1)
    {

	
	bit_lido = PORTGbits.RG7;
	
	if (bit_lido==0 && escutar==0){
		resetCoreTimer();
		escutar=1;
		contagem_bit=1;
		leituras[0]='0';
		/*printf("leu o primeiro"); */
		
		}
		
	if (escutar==1 && contagem_bit==1  && readCoreTimer()>= 13000 /*325microsegundos*/){

		if (bit_lido==0){
			espera=26000;
			leituras[1]='0';
			
		}
		if (bit_lido==1){
			espera=22000;
			leituras[1]='1';
			
		}
		contagem_bit=2;
		/*printf("leu o segundo");
		printf( "\n" );*/
		resetCoreTimer();
		}
		
	while (contagem_bit<31 && contagem_bit>=2) {
		
		if (readCoreTimer()>=espera) {
			
		bit_lido = PORTGbits.RG7;
		
			if (bit_lido==0){
			espera=26000;
			leituras[contagem_bit]='0';
			
			}
			if (bit_lido==1){
			espera=22000;
			leituras[contagem_bit]='1';
		
			}
			contagem_bit=contagem_bit+1;
			resetCoreTimer();
			/*printf("leu os outros");
			printf( "\n" );*/
		}
		
			
		
	}
	

	
	if (contagem_bit==31) {	
		contagem_bit=0; 
		escutar= 0; 

		
		for(i=0;i<32;i++){
			putChar(leituras[i]);
	
		}
	printf( "\n" );
	

 

		
	if (strcmp(leituras, desligar)==0){
		setVel2(0,0);
		printf("parar");
		printf( "\n" );
		}
		
	if (strcmp(leituras, frente)==0){
		setVel2(40,40);
		printf("andar");
		printf( "\n" );
		}
		
	if (strcmp(leituras, tras)==0){
		setVel2(-40,-40);
		printf("tras");
		printf( "\n" );
		}
		
	if (strcmp(leituras, peao)==0){
		setVel2(-40,40);
		printf("peao");
		printf( "\n" );
		}
		
	if (strcmp(leituras, direita)==0){
		setVel2(40,-40);
		printf("direita");
		printf( "\n" );
		wait(1);
		}
	if (strcmp(leituras, esquerda)==0){
		setVel2(-40,40);
		printf("esquerda");
		printf( "\n" );
		wait(1);
		}

			
	strncpy( leituras, "11111111111111111111111111111111", sizeof( leituras ) );



	}
	

	
	}
  
  return (0);
  
}
