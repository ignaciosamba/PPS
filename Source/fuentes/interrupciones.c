/**
 * @file interrupciones.c
 * @author Sambataro, Ignacio; Mantovani, Luciano
 * @date 2015
 * @brief define todas las rutinas de interrupcion
 * @details [long description]
 */
#include "headers.h"
#include "sensorCE/funciones_sensor.h"
#include "interrupciones.h"
#include "configurador.h"
#include "conversor.h"

sbit LED = P0^7;

/**
 * @brief rutina de interrupcion para el ADC
 * @details Reinicia la bandera de interrupcion por conversion terminada y habilita un flag que se evalua en la funcion principal y hace que se ponga en funcionamiento el procesamiento de los datos convertidos.
 */
void ADC0_ISR (void) interrupt 10
{
   while(!AD0INT);                     // Wait till conversion complete
   AD0INT = 0;                         // Clear ADC0 conversion complete flag
   f_dato_convertido = true;
   // LED = ~LED;
}
/**
 * @brief rutina de interrpucion para la UART
 * @details es usada para detectar una entrada por teclado cuando el programa esta convirtiendo y se desea volver a la etapa de configuracion
 */
 void UART_ISR (void) interrupt 4
 {
    if(RI0 == 1)
    {                         // Se borra el bit de dato recibido en la UART
		RI0 = 0;
 		f_UART = true;
 		
	    if(f_sleep)
	    {
	    	f_sleep = 0;
	    	deshabilitar_modo_bajo_consumo();
	    }

    }

    //LED = ~LED;
 }

 /**
  * @brief Rutina de interrupcion para Timer 3
  * @details Esta funcion se ejecuta en cada interrupcion por overflow del timer 3. Esto ocurre aproximadamente cada 32 ms. La usamos para dos cosas, cuando el motor esta andando, sienta la base de tiempo para el control del motor. Tanto si el motor esta o no andando, sienta la base de tiempo para la medicion del timestamp relativo entre conversiones
  * */
 void T3_ISR(void) interrupt 14
 {
	static short int i = 0;

 	TMR3CN &= ~(1 << 7); // volver a 0 la bandera de interrupcion del byte superior
 	TMR3CN &= ~(1 << 6); // volver a 0 la bandera de interrupcion del byte inferior

	// timer3 es de 16 bits, por lo que en un segundo, timer3 interrumpe 2041666/65536 = 31 veces
	// si i == 3, pasaron aproximadamente 100 ms
  	if(i >= 3)
 	{
		contar_RPM(); 
 		i = 0;
 	}
	i++;
 }

  void T2_ISR(void) interrupt 5
 {
 	static short int i = 0;
 
	TMR2CN &= ~(1 << 7); // volver a 0 la bandera de interrupcion del byte superior
 	TMR2CN &= ~(1 << 6); // volver a 0 la bandera de interrupcion del byte inferior

	// Con timer en modo partido: 
	// timer2L es de 8 bits, por lo que en un segundo, timer2 interrumpe 2041666/256 = 7975 veces

	// Con timer en modo 16 bits:
	// timer2 es de 16 bits, por lo que en un segundo, timer2 interrumpe 2041666/65536 = 31 veces
 	i++;

	actualizar_timestamp(i);

	if(i >= 10000)
		i = 0;
 }