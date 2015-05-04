/**
 * @file interrupciones.c
 * @author Sambataro, Ignacio; Mantovani, Luciano
 * @date 2015
 * @brief define todas las rutinas de interrupcion
 * @details [long description]
 */
#include "headers.h"
#include "interrupciones.h"


void ADC0_ISR (void) interrupt 10
{
   static LONGDATA rawValue;
   unsigned long mV;

   while(!AD0INT);                     // Wait till conversion complete
   AD0INT = 0;                         // Clear ADC0 conversion complete flag

   // Copy the output value of the ADC
   rawValue.Byte[Byte3] = 0x00;
   rawValue.Byte[Byte2] = (unsigned char)ADC0H;
   rawValue.Byte[Byte1] = (unsigned char)ADC0M;
   rawValue.Byte[Byte0] = (unsigned char)ADC0L;

   //                           Vref (mV)
   //   measurement (mV) =   --------------- * result (bits)
   //                       (2^24)-1 (bits)
   //
   //   measurement (mV) =  result (bits) / ((2^24)-1 (bits) / Vref (mV))
   //
   //
   //   With a Vref (mV) of 2500:
   //
   //   measurement (mV) =  result (bits) / ((2^24)-1 / 2500)
   //
   //   measurement (mV) =  result (bits) / ((2^24)-1 / 2500)
   //
   //   measurement (mV) =  result (bits) / (16777215 / 2500)
   //
   //   measurement (mV) =  result (bits) / (6710)

   mV = rawValue.result / 6710;        // Because of bounds issues, this
                                       // calculation has been manipulated as
                                       // shown above
                                       // (i.e. 2500 (VREF) * 2^24 (ADC result)
                                       // is greater than 2^32)

   printf("AIN0.2 voltage: %4ld mV\n",mV);
}