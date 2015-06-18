/**
 * @file interrupciones.c
 * @author Sambataro, Ignacio; Mantovani, Luciano
 * @date 2015
 * @brief define todas las rutinas de interrupcion
 * @details [long description]
 */
#include "headers_hw.h"
#include "headers_logic.h"
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