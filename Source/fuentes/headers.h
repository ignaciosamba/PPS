#include <C8051F350.h>
#include <stdio.h>
#include <stdlib.h>

#define SYSCLK      24500000           // SYSCLK Frecuencia del Clock en Hertz
#define MDCLK         2457600          // Modulator clock in Hz (ideal i
#define OWR                20          // Desired Output Word Rate in Hz
#define BAUDRATE        115200           // Baudios del UART
#define TAM_SINGLE 			 8 			//define para tamaño de buffer! 
//-----------------------------------------------------------------------------
// 16-bit SFR Definitions for 'F35x
//-----------------------------------------------------------------------------

sfr16 TMR2RL = 0xCA;                   // Timer2 reload value
sfr16 TMR2 = 0xCC;                     // Timer2 counter
sfr16 ADC0DEC = 0x9A;                  // ADC0 Decimation Ratio Register


// With the Keil compiler and union byte addressing:
// [0] = bits 31-24, [1] =  bits 23-16, [2] = bits 15-8, [3] = bits 7-0
#define Byte3 0
#define Byte2 1
#define Byte1 2
#define Byte0 3

/*typedefs*/

typedef union LONGDATA{                // Access LONGDATA as an
   unsigned long result;               // unsigned long variable or
   unsigned char Byte[4];              // 4 unsigned byte variables
}LONGDATA;

typedef char byte;
#define ARRAYSIZE 8

typedef enum { false, true } bool;

// /*variables globales*/
// unsigned long dato_convertido;
// unsigned short pin_actual;


/*FLAGS globales*/

extern bool f_dato_convertido;
extern int buffer_single [TAM_SINGLE];
