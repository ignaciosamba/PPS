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
 
short int posicion_adc;
long int dato_a_enviar;
 bit f_dato_convertido;

 char bdata buffer_single;
 sbit buffer_single_0 = buffer_single ^ 0;
 sbit buffer_single_1 = buffer_single ^ 1;
 sbit buffer_single_2 = buffer_single ^ 2;
 sbit buffer_single_3 = buffer_single ^ 3;
 sbit buffer_single_4 = buffer_single ^ 4;
 sbit buffer_single_5 = buffer_single ^ 5;
 sbit buffer_single_6 = buffer_single ^ 6;
 sbit buffer_single_7 = buffer_single ^ 7;

void main(void)
{
	short int i = 0;
   	PCA0MD &= ~0x40;                    // WDTE = 0 (clear watchdog timer 

    buffer_single = 0;	

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
			enviar_dato(&dato_a_enviar);
			posicion_adc = cambiar_pin();
			seleccionar_puerto(posicion_adc);
		}
	}


}