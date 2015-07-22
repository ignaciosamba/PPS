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

void ADC0_ISR (void) interrupt 10
{
   // printf("hola, acabo de convertir\n");
   while(!AD0INT);                     // Wait till conversion complete
   AD0INT = 0;                         // Clear ADC0 conversion complete flag
   f_dato_convertido = true;
   // LED = ~LED;
}
 void UART_ISR (void) interrupt 4
 {
    if(RI0 == 1)
    {                         // Se borra el bit de dato recibido en la UART
		RI0 = 0;
 		f_UART = true;
    }
    //LED = ~LED;
 }