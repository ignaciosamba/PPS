/**
 * @file interrupciones.c
 * @author Sambataro, Ignacio; Mantovani, Luciano
 * @date 2015
 * @brief define todas las rutinas de interrupcion
 * @details [long description]
 */
#include "headers.h"
#include "interrupciones.h"

sbit LED = P0^7;

/**
 * @brief rutina de interrupcion para el ADC
 * @details simplemente reinicia la bandera de interrupcion por conversion terminada y habilita un flag que se 
 * evalua en la funcion principal y hace que se ponga en funcionamiento el procesamiento de los datos convertidos
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
 * @details es usada para detectar una entrada por teclado cuando el programa esta convirtiendo y se desea volver
 * a la etapa de configuracion
 */
 void UART_ISR (void) interrupt 4
 {
    if(RI0 == 1)
    {                         // Se borra el bit de dato recibido en la UART
		RI0 = 0;
 		f_UART = true;
    }
    //LED = ~LED;
 }