//-----------------------------------------------------------------------------
// F35x_Timer0_16bitTimer.c
//-----------------------------------------------------------------------------
// Copyright 2005 Silicon Laboratories, Inc.
// http://www.silabs.com
//
// Program Description:
//
// This program presents an example of use of the Timer0 of the C8051F35x's in
// 16-bit counter/timer mode. It uses the 'F350DK as HW platform.
// In this example the LED is toggled at a rate defined by the
// LED_TOGGLE_RATE constant.(in milliseconds)
//
// The timer is set with this values and counts until an overflow when it
// generates an interrupt. This interrupt reloads the timer values and toggles
// the LED.
//
// Pinout:
//
//    P0.6 -> LED
//
//    all other port pins unused
//
// How To Test:
//
// 1) Open the F35x_Timer0_16bitTimer.c file in the Silicon Labs IDE.
// 2) If another rate is required change LED_TOGGLE_RATE (in msec)
// 3) Compile the project and download to the device.
// 4) Verify the LED pins of J3 are populated on the 'F35x TB.
// 6) Run the code.
// 7) Check that the LED is blinking at a constant rate .
//
//
// FID:            35X000024
// Target:         C8051F35x
// Tool chain:     KEIL C51 7.20 / KEIL EVAL C51
// Command Line:   None
//
// Release 1.0
//    -Initial Revision (CG)
//    -14 DEC 2005
//

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------

#include <C8051F350.h>                 // SFR declarations
#include <stdio.h>                 // SFR declarations

//-----------------------------------------------------------------------------
// Global Constants
//-----------------------------------------------------------------------------

// #define SYSCLK             24500000/8  // SYSCLK in Hz (24.5 MHz internal
                                       // oscillator / 8)
                                       // the internal oscillator has a
                                       // tolerance of +/- 2%
#define SYSCLK                      24500000  
#define OWR                         20          // Desired Output Word Rate in Hz
#define BAUDRATE                    115200           // Baudios del UART

#define TIMER_PRESCALER             48  // Based on Timer CKCON settings

#define LED_TOGGLE_RATE             50  // LED toggle rate in milliseconds
                                       // if LED_TOGGLE_RATE = 1, the LED will
                                       // be on for 1 millisecond and off for
                                       // 1 millisecond

// There are SYSCLK/TIMER_PRESCALER timer ticks per second, so
// SYSCLK/TIMER_PRESCALER/1000 timer ticks per millisecond.
#define TIMER_TICKS_PER_MS  SYSCLK/TIMER_PRESCALER/1000

// Note: LED_TOGGLE_RATE*TIMER_TICKS_PER_MS should not exceed 65535 (0xFFFF)
// for the 16-bit timer

#define AUX1     TIMER_TICKS_PER_MS*LED_TOGGLE_RATE
#define AUX2     -AUX1
#define AUX3     0x00
#define AUX4     0x00

#define TIMER0_RELOAD_HIGH       AUX4  // Reload value for Timer0 high byte
#define TIMER0_RELOAD_LOW        AUX3  // Reload value for Timer0 low byte

sbit LED = P0^6;                       // LED='1' means ON

//-----------------------------------------------------------------------------
// Function Prototypes
//-----------------------------------------------------------------------------


#define Byte3 0
#define Byte2 1
#define Byte1 2
#define Byte0 3


/*typedefs*/

typedef union LONGDATA{                // Access LONGDATA as an
   unsigned long result;               // unsigned long variable or
   unsigned char Byte[4];              // 4 unsigned byte variables
}LONGDATA;


int iniciar_UART(void);
void iniciar_osc_externo(void);
void Port_Init (void);                 // Port initialization routine
void Timer2_Init (void);               // Timer0 initialization routine
void iniciar_sysclock(void);

//-----------------------------------------------------------------------------
// main() Routine
//-----------------------------------------------------------------------------

void main (void)
{
   static LONGDATA rawValue;
   unsigned long res = 0;
   PCA0MD &= ~0x40;                    // Clear watchdog timer enable
   iniciar_sysclock();
   iniciar_osc_externo();
   Timer2_Init ();                     // Initialize the Timer2
   Port_Init ();                       // Init Ports
   iniciar_UART();
   // EA = 1;                             // Enable global interrupts


   while (1){

   // printf("holaaaaa\n");

   
   
      rawValue.Byte[Byte3] = 0x00;
      rawValue.Byte[Byte2] = 0x00;
      rawValue.Byte[Byte1] = (unsigned char)TMR2H;
      rawValue.Byte[Byte0] = (unsigned char)TMR2L;

      res = rawValue.result;
      
      printf("Contador : %lu\n", res * 8);
   
   
   }                          // Loop forever
}

//-----------------------------------------------------------------------------
// Initialization Subroutines
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Port_Init
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// This function configures the crossbar and GPIO ports.
//
// Pinout:
//
//    P0.6 -> LED
//
//    all other port pins unused
//
//-----------------------------------------------------------------------------
void Port_Init (void)
{
   XBR1 = 0x40;                        // Enable crossbar, and habilitar T0
   XBR0 |= 0x01;                    // Enable UART on P0.4(TX) and P0.5(RX)  
   P0MDIN |= 0x08;                   
   // P0MDIN = 0xFF;                     //
   // IE |= 0x01;
   // P0MDOUT = 0x00;					//Pines configurados como salida push-pull. 
   // P0 = 0xFF;
   // IE |= 0X01;
   // IT01CF |= 0x08;
   // P0SKIP = 0x01;
   // P0SKIP = 0x00;				//Los pines desde 0.7 a 0.1 lo saltea la crossbar
}
//-----------------------------------------------------------------------------
// Timer2_Init
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// This function configures the Timer0 as a 16-bit timer, interrupt enabled.
// Using the internal osc. at 24.5MHz with a prescaler of 1:8 and reloading the
// T0 registers with TIMER0_RELOAD_HIGH/LOW it will interrupt and then toggle
// the LED.
//
// Note: The Timer0 uses a 1:48 prescaler.  If this setting changes, the
// TIMER_PRESCALER constant must also be changed.
//-----------------------------------------------------------------------------
void Timer2_Init(void)
{
   TMR2CN |= 0x05; // T2 en modo 16 bits, TR2 habilitado, clockeado por fuente externa
   TMR2L = 0;
   TMR2H = 0;
}


//-----------------------------------------------------------------------------
// Interrupt Service Routines
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Timer0_ISR
//-----------------------------------------------------------------------------
//
// Here we process the Timer0 interrupt and toggle the LED
//
//-----------------------------------------------------------------------------
// void Timer0_ISR (void) interrupt 1
// {
//    LED = ~LED;                         // Toggle the LED
//    TH0 = TIMER0_RELOAD_HIGH;           // Reinit Timer0 High register
//    TL0 = TIMER0_RELOAD_LOW;            // Reinit Timer0 Low register
// }

//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------


int iniciar_UART(void)
{

   SCON0 = 0x10;                       // SCON0: 8-bit variable bit rate
                                      //        level of STOP bit is ignored
                                      //        RX enabled
                                      //        ninth bits are zeros
                                      //        clear RI0 and TI0 bits
   if (SYSCLK/BAUDRATE/2/256 < 1) 
   {
      TH1 = -(SYSCLK/BAUDRATE/2);
      CKCON &= ~0x0B;                  // T1M = 1; SCA1:0 = xx
      CKCON |=  0x08;
   } 
   else if (SYSCLK/BAUDRATE/2/256 < 4) 
   {
      TH1 = -(SYSCLK/BAUDRATE/2/4);
      CKCON &= ~0x0B;                  // T1M = 0; SCA1:0 = 01                  
      CKCON |=  0x01;
   } 
   else if (SYSCLK/BAUDRATE/2/256 < 12) 
   {
      TH1 = -(SYSCLK/BAUDRATE/2/12);
      CKCON &= ~0x0B;                  // T1M = 0; SCA1:0 = 00
   } 
   else 
   {
      TH1 = -(SYSCLK/BAUDRATE/2/48);
      CKCON &= ~0x0B;                  // T1M = 0; SCA1:0 = 10
      CKCON |=  0x02;
   }

   TL1 = TH1;                          // Init Timer1
   TMOD &= ~0xf0;                      // TMOD: timer 1 in 8-bit autoreload
   TMOD |=  0x20;                       
   TR1 = 1;                            // START Timer1
   TI0 = 1;                            // Indicate TX0 ready

   return 0;
}

void iniciar_sysclock (void)
{
   OSCICN |= 0x03;                     // configuracion del oscilador para la maxima frecuencia
   RSTSRC  = 0x04;                     // Enable missing clock detector
}

void iniciar_osc_externo(void)
{
   OSCXCN |= 0x20; // seleccionar oscilador externo en modo CMOS Clock mode. Bits de control de frecuencia 0
}