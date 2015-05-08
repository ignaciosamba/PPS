/**
 * @file main.c
 * @author Sambataro, Ignacio; Mantovani, Luciano
 * @date 2015
 * @brief [brief description]
 * @details [long description]
 */
#include "headers.h"
#include "interfaz.h"
#include "configurador.h"
#include "conversor.h"
#include "control.h"

 
long int dato_a_enviar;
int buffer_single [TAM_SINGLE]; 
char puerto;
bool f_dato_convertido;



void main(void)
{

   	PCA0MD &= ~0x40;                    // WDTE = 0 (clear watchdog timer 
   	buffer_single [TAM_SINGLE] = malloc(TAM_SINGLE);

	iniciar_sysclock();
	iniciar_puertos();
	iniciar_UART();
	printf("Volvi arriba una mocha\n");
	correr_menu();
	printf("sali del menu!!!! \n");
	iniciar_ADC();
	//puerto = cambiar_pin();
	//seleccionar_puerto(puerto);

	AD0INT = 0;							
	ADC0MD = 0x83;                      // Start continuous conversions
	EA = 1;   	                        // Enable global interrupts
	//ADC0MUX
	while(1)
	{

		// printf("no entraaa\n");
		//necesitas contador para leer el arreglo de puertos
		
		if(f_dato_convertido)
		{
			//lees el dato correspondiente a la posicion del arreglo
			//llamas a seleccionar_puerto(parametro el numero de puerto que lee del arreglo)
			puerto = cambiar_pin();
			seleccionar_puerto(puerto);
			f_dato_convertido = false;
			dato_a_enviar = convertir();
			enviar_dato(dato_a_enviar);
			//cambiar_pin ();
		}
		//incrementas contador;
		//if (cont >= tam del arreglo) cont= 0;
	}
}

