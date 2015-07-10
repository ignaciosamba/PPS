/**
 * @file headers_hw.h
 * @author Sambataro, Ignacio; Mantovani, Luciano
 * @date 2015
 * @brief establece las librerias y define las variables que caen dentro del campo del funcionamiento del\
 * microcontrolador. 
 */
#include "C8051F350.h"
#pragma ot(11, SIZE)  // optimiza la compilacion

#define SYSCLK      24500000           // SYSCLK Frecuencia del Clock en Hertz
#define MDCLK         2457600          // Frecuencia del clock del modulador (ideal = 2,4576 MHz)
#define OWR                300          // Output Word Rate deseado
#define BAUDRATE        115200           // Tasa de baudios de la UART
//-----------------------------------------------------------------------------
// 16-bit SFR Definitions for 'F35x
//-----------------------------------------------------------------------------
sfr16 TMR2RL = 0xCA;                   // Timer2 reload value
sfr16 TMR2 = 0xCC;                     // Timer2 counter
sfr16 ADC0DEC = 0x9A;                  // ADC0 Decimation Ratio Register


#define Byte3 0
#define Byte2 1
#define Byte1 2
#define Byte0 3



typedef union LONGDATA{                // Access LONGDATA as an
   unsigned long result;               // unsigned long variable or
   unsigned char Byte[4];              // 4 unsigned byte variables
}LONGDATA;

