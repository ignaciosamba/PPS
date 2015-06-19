/**
 * @file main.c
 * @author Sambataro, Ignacio; Mantovani, Luciano
 * @date 2015
 * @brief [brief description]
 * @details [long description]
 */
#include "headers_hw.h"
#include "headers_logic.h"
#include "interfaz.h"
#include "configurador.h"
#include "conversor_hw.h"
#include "conversor_logic.h"
 
unsigned long int dato_a_enviar;
bool f_dato_convertido;
unsigned short int posicion_adc;
short int bandera_dif;
sbit LED = P0^7;                          // LED='1' means ON

void main(void)
{

   	struct shellstr *shell; 
	char i = 0;
   	PCA0MD &= ~0x40;                    // WDTE = 0 (clear watchdog timer
    shell = (struct shellstr *) malloc(sizeof(struct shellstr));
   	shell->buffer_adc = malloc(TAM_SINGLE);

   	if(shell == NULL || shell->buffer_adc == NULL)
   	{
   		printf("no hay lugar para shell!!\n");
   		while(1);
   	}

   	for (i=0 ; i<TAM_SINGLE ; i++)
   		shell->buffer_adc[i]=0;

	iniciar_sysclock();
	iniciar_puertos();
	iniciar_osc_externo();
	iniciar_UART();
	iniciar_ADC();
	iniciar_timer0();
	iniciar_timer2();
	// iniciar_timer3();
	// iniciar_PCA();



	shell->stop_conf = 1;

	while(shell->stop_conf == 1)
	{
		restart(shell);

		obtener_entrada(shell);

		// printeartodo(shell);
		if(shell->errn != 0)
		{
			reportar(shell);
		}
		else
		{
			analizar(shell);
			reportar(shell);
		}
	}

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
			// LED = ~LED;
			cambiar_pin();
		}
	}

	// free(shell->buffer_adc);
	// free(shell);
}