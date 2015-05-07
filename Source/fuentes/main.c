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
 
long int dato_a_enviar;
bool f_dato_convertido;

void main(void)
{

   	PCA0MD &= ~0x40;                    // WDTE = 0 (clear watchdog timer 


	iniciar_sysclock();
	iniciar_puertos();
	iniciar_UART();
	iniciar_ADC();
	// correr_menu();

	AD0INT = 0;							
	ADC0MD = 0x83;                      // Start continuous conversions
	EA = 1;                             // Enable global interrupts

	while(1)
	{
		// printf("no entraaa\n");
		if(f_dato_convertido)
		{
			printf("AAAAAAAAAAAAAAA\n");
			f_dato_convertido = false;
			dato_a_enviar = convertir();
			enviar_dato(dato_a_enviar);
			//cambiar_pin ();
		}
	}
}