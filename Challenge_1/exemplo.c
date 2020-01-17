#include "mr32.h"
/*
 * exemplo.c
 *
 * Imprime no ecrã a tensão das baterias.
 *
 */

int
main (void)
{
  /* Variable declarations go here */
  int tensao_dV; 		/* Tensão das baterias, em décimas de V */

  int tensao_V;			/* Tensao das baterias, em V, parte inteira */
  int tensao_Vf;		/* Tensao das baterias, em V, parte fracional */

  /* initPIC32() makes all the required initializations to the
   * PIC32 hardware platform */
  initPIC32 ();

  // readSensors();

  /* Lê tensão nas baterias (em dV) */
  tensao_dV = batteryVoltage();

  /* Converte tensão para Volts (parte inteira e parte fracional) */
  tensao_V = tensao_dV/10;	/* parte inteira */
  tensao_Vf = tensao_dV - 10*tensao_V; /* parte fracional */

  /* Imprime resultados */
  printStr("Tensao nas baterias: ");
  printInt10(tensao_V);
  printStr(".");
  printInt10(tensao_Vf);
  printStr(" V\n");

  /* Ciclo principal; ignorado */
  while (1)
    {
      /* Code goes here */
    }
  return (0);
}
