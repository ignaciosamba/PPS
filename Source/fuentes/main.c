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
int buffer_single [TAM_SINGLE]; 
short int posicion_adc;

void main(void)
{
	int i = 0;
   	PCA0MD &= ~0x40;                    // WDTE = 0 (clear watchdog timer 
   	for (i=0 ; i<0 ; i++)
   		buffer_single[i]=0;
   	buffer_single [TAM_SINGLE] = malloc(TAM_SINGLE);
	iniciar_sysclock();
	iniciar_puertos();
	iniciar_UART();
	iniciar_ADC();
	correr_menu();

	AD0INT = 0;							
	ADC0MD = 0x83;                      // Start continuous conversions
	EA = 1;                             // Enable global interrupts

	while(1)
	{
		// empezar_adc();
		if(f_dato_convertido)
		{
			f_dato_convertido = false;
			dato_a_enviar = convertir();
			enviar_dato(dato_a_enviar);
			posicion_adc = cambiar_pin();
			seleccionar_puerto(posicion_adc);
		}
	}
}