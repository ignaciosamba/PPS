/**
 * @file main.c
 * @author Sambataro, Ignacio; Mantovani, Luciano
 * @date 2015
 * @brief define la funcion principal, define todas las variables globales
 */
#include "headers.h"
#include "interfaz.h"
#include "configurador.h"
#include "conversor.h"
#include "sensorCE/funciones_sensor.h"
 
unsigned long int dato_a_enviar;
unsigned short int posicion_adc;
short int bandera_dif;
sbit LED = P0^7;                          // LED='1' means ON

bool f_dato_convertido;
bool f_UART;
bool f_contRPM;
bool f_sleep;
/**
 * @brief funcion principal, inicializa todos los parametros y corre las funciones principales
 */
void main()
{
   	struct shellstr *shell; 
	char i = 0;
   	PCA0MD &= ~0x40;                    // deshabilitar el watchdog timer

    shell = (struct shellstr *) malloc(sizeof(struct shellstr));
   	shell->var = 0; // inicializar en 0 la variable auxiliar para la funcion analizar_buffer
   	shell->conversion_active = false;

   	if(shell == NULL)
   	{
   		printf("no hay lugar para shell!!\n");
   		while(1);
   	}

   	//inicializa el buffer de valores estaticos en 0
   	for (i=0 ; i<TAM_SINGLE ; i++)
   		shell->buffer_adc_count[i]=0;

   	//inicializa la bandera de sleep en 0
   	f_sleep = 0;

	iniciar_sysclock();
	iniciar_puertos();
	iniciar_osc_externo();
	iniciar_UART();
	iniciar_PCA();
	iniciar_ADC();
	iniciar_timer0();
	iniciar_timer2();
	iniciar_contadorRPM();
	// iniciar_timer3();

	shell->stop_conf = 1;

	while (1)
		{

			// comienza ciclo infinito hasta que se de la orden de parar la configuracion	
			while(shell->stop_conf == 1)
			{
				restart(shell);		// reinicia los arreglos de obtencion de comandos
				obtener_entrada(shell); 

				if(shell->report != 0) // si hay un error, el comando no se analiza
				{
					reportar(shell); 
				}
				else
				{
					analizar(shell);
					reportar(shell);  // si hay un error en el analisis, hay que reportarlo
				}
			}

			// se inicializa el buffer temporal
			for(i = 0; i < TAM_SINGLE; i++)
			{
				shell->buffer_adc[i] = shell->buffer_adc_count[i];
			}

			AD0INT = 0;		// se inicializa en 0 el bit de conversion completa del ADC	
			ADC0MUX = 0x08;  // el primer pin a analizar es el pin 0 en modo single-ended
			ADC0MD = 0x83;	// Habilitar conversion en modo continuo
			EIE1 |= 0x08;    // Habilitar interrupciones del ADC
			EA = 1;          // habilitar interrupciones globales
			// ES0 = 1;


			while(1)
			{
				// empezar_adc();
				shell->conversion_active = true;
			    ES0 = 1; // habilitar interrupcion de UART

			    //monitoriza entrada serial
				if (f_UART)
			    {	
			    	int recibido = (int)SBUF0;
					f_UART = false;
			    	//printf("STOP. message: '%c'\n", (char)recibido);

			    	if(recibido == 112) // 112 es 'p' en ascii
			    	{
			    		// printf("stillOn\n");
						shell->conversion_active = false;
						refresh_watchDog();
				    	shell->report = 501; // stillOn successful
				    	reportar(shell);
					}
			    	else if(recibido == 115) //115 es 's' en ascii
			    	{
						ADC0MD = 0x00; // conversion inhabilitada
						EA = 0; // inhabilitar interrupciones globales
						shell->stop_conf = 1;
				    	shell->report = 500; // stop succesful
				    	reportar(shell);

				    	break;
			    	}
			    }

			    ES0 = 0; // deshabilitar interrupcion de UART
				if(f_dato_convertido)
				{
					f_dato_convertido = false;
					dato_a_enviar = convertir();

					if(analizar_buffer(shell))
					{
						enviar_dato(&dato_a_enviar);
						// mostrar_config_actual(shell);
					}
					// LED = ~LED;
					cambiar_pin();
				}

			}
		}
}