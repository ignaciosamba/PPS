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
short int envio_st;
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
	// iniciar_timer2();
	iniciar_contadorRPM();
	// iniciar_timer3();

	shell->stop_conf = 1;
	//printf("00000");

	while (1)
		{

			// comienza ciclo infinito hasta que se de la orden de parar la configuracion	
			while(shell->stop_conf == 1)
			{
				restart(shell);		// reinicia los arreglos de obtencion de comandos
				obtener_entrada(shell); 

				if(shell->errn != 0) // si hay un error, el comando no se analiza
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
			EIE1 |= 0x08;    // Enable ADC0 Interrupts
			EA = 1;          // habilitar interrupciones globales
			// ES0 = 1;


			while(1)
			{
				// empezar_adc();
				shell->conversion_active = true;
			    ES0 = 1; // habilitar interrupcion de UART
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
				    	shell->errn = 501; // stillOn successful
				    	reportar(shell);
					}
			    	else if(recibido == 115) //115 es 's' en ascii
			    	{
						ADC0MD = 0x00; // conversion inhabilitada
						EA = 0; // inhabilitar interrupciones globales
						shell->stop_conf = 1;
				    	shell->errn = 500; // stop succesful
				    	reportar(shell);

				    	break;
			    	}
			    	else if (recibido == 101) //101 es 'e' en ascci 
			    	{
			    		envio_st = 1
			    		if (sizeof(buffer_intermedio) == 0)
			    		{
				    		shell->errn = 504; //Buffer de Conversion intermedio vacio.
				    		reportar(shell);
				    	}
				    	else 
				    	{
				    		shell-errn = 503; //El buffer tiene datos para chupar.
				    		reportar(shell);
				    	}
			    	}
			    }

			    ES0 = 0; // deshabilitar interrupcion de UART
				if(f_dato_convertido)
				{
					f_dato_convertido = false;
					dato_a_enviar = convertir();
					//obtengo el dato de la conversion, ahora lo tengo que meter en el buffer.
					if (sizeof(buffer_intermedio) =< 20)
					{	
						//el buffer tiene espacio, por lo tanto guardo la conversion en el mismo buffer.
					}

					if(analizar_buffer(shell))
					{
						if (envio_st = 1) //si esta en 1 esta variable entonces se mando una 'e' desde el servidor, y estoy habilidatod a enviar datos.
						{				  //Recordar que la 'e' se envia cuando se quiere leer algo desde el buffer.
							envio_st = 0;
							if(sizeof(buffer_intermedio) > 0)
							{
								enviar_dato(&dato_a_enviar);
								// mostrar_config_actual(shell);
							}
							if (sizeof(buffer_intermedio) == 0)
							{
								printf("%05d", 504); //se informa al servidor que no hay datos en el buffer
							}
						}
					}
					// LED = ~LED;
					cambiar_pin();
				}

			}
		}
	// free(shell->buffer_adc);
	// free(shell);
}