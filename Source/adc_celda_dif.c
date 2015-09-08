//-----------------------------------------------------------------------------   
// Includes   
//----------------------------------------------------------------------------- 

#include <C8051F350.h>                 // SFR declarations   
#include <stdio.h>   

//-----------------------------------------------------------------------------   
// 16-bit SFR Definitions for 'F35x   
//-----------------------------------------------------------------------------   
   
sfr16 TMR2RL = 0xCA;                   // Timer2 reload value   
sfr16 TMR2 = 0xCC;                     // Timer2 counter   
sfr16 ADC0DEC = 0x9A;                  // ADC0 Decimation Ratio Register   
sbit LED = P0^6;                          // LED='1' means ON
   
//-----------------------------------------------------------------------------   
// Global CONSTANTS   
//-----------------------------------------------------------------------------   
   
#define SYSCLK       24500000          // SYSCLK frequency in Hz   
   
#define MDCLK         2457600          // Modulator clock in Hz (ideal is   
                                       // (2.4576 MHz)   
#define OWR                20          // Desired Output Word Rate in Hz   
   
#define BAUDRATE       115200          // Baud rate of UART in bps   
   
typedef union LONGDATA{                // Access LONGDATA as an   
   unsigned long result;               // unsigned long variable or   
   unsigned char Byte[4];              // 4 unsigned byte variables   
}LONGDATA;   
   
// With the Keil compiler and union byte addressing:   
// [0] = bits 31-24, [1] =  bits 23-16, [2] = bits 15-8, [3] = bits 7-0   
#define Byte3 0   
#define Byte2 1   
#define Byte1 2   
#define Byte0 3   
   
//-----------------------------------------------------------------------------   
// Function PROTOTYPES   
//-----------------------------------------------------------------------------   
   
void Oscillator_Init (void);   
void Port_Init (void);   
void UART0_Init (void);   
void ADC0_Init(void);   
void Timer3_Init(int counts);
   
//-----------------------------------------------------------------------------   
// MAIN Routine   
//-----------------------------------------------------------------------------   
void main (void)   
{   
   PCA0MD &= ~0x40;                    // WDTE = 0 (clear watchdog timer   
                                       // enable)   
   
   Oscillator_Init();                  // Initialize system clock   
   Port_Init();                        // Initialize Crossbar and GPIO   
   UART0_Init();                       // Initialize UART0 for printf's   
   ADC0_Init();                        // Initialize ADC0   


   Timer3_Init (SYSCLK / 12 / 1);        // Init Timer3 to generate
   
   AD0INT = 0;   
   ADC0MD = 0x82;                      // Start continuous conversions   
   EA = 1;                             // Enable global interrupts   
   
   while (1) {                         // Spin forever   
   }   
}   
   
//-----------------------------------------------------------------------------   
// Initialization Subroutines   
//-----------------------------------------------------------------------------   
   
//-----------------------------------------------------------------------------   
// Oscillator_Init   
//-----------------------------------------------------------------------------   
//   
// Return Value : None   
// Parameters   : None   
//   
// This routine initializes the system clock to use the internal 24.5MHz   
// oscillator as its clock source.  Also enables missing clock detector reset.   
//   
//-----------------------------------------------------------------------------   
void Oscillator_Init (void)   
{   
   OSCICN = 0x83;                      // Configure internal oscillator for   
                                       // its lowest frequency-DIVIDIDO EN UNO!
   RSTSRC = 0x04;                      // Enable missing clock detector   
}   
   
//-----------------------------------------------------------------------------   
// Port_Init   
//-----------------------------------------------------------------------------   
//   
// Return Value : None   
// Parameters   : None   
//   
// This function initializes the GPIO and the Crossbar   
//   
// Pinout:   
//   
//   P0.4 - UART TX (digital, push-pull)   
//   P0.5 - UART RX (digital, open-drain)   
//   
//   AIN0.2 - ADC0 input   
//   
//-----------------------------------------------------------------------------   
void Port_Init (void)   
{   
   XBR0 |= 0x01;                        // UART0 Selected   
   XBR1 |= 0x40;                        // Enable crossbar and weak pull-ups   
   P0MDOUT |= 0xD0;                    // TX, LEDs = Push-pull   
}   
   
//-----------------------------------------------------------------------------   
// UART0_Init   
//-----------------------------------------------------------------------------   
//   
// Return Value : None   
// Parameters   : None   
//   
// Configure the UART0 using Timer1, for <BAUDRATE> and 8-N-1.   
//   
//-----------------------------------------------------------------------------   
void UART0_Init (void)
{

//-----------------------------------------------------------------------------
// UART0_Init
//-----------------------------------------------------------------------------
//
// Configure the UART0 using Timer1, for <BAUDRATE> and 8-N-1.
//
   
   XBR0     |= 0x01;                    // Enable UART to Pins P0.4, P0.5
   XBR1     |= 0x40;                    // Enable Crossbar 

   P0SKIP   = 0x00;                    // Skip No Port Pins
   P0MDOUT |= 0x10;                    // Enable UTX as push-pull output
   P0MDIN  |= 0x20;                 // Enable URX pin as digital input.
   
   
   
   SCON0 = 0x13;                       // SCON0: 8-bit variable bit rate
                                       //        level of STOP bit is ignored
                                       //        RX enabled
                                       //        ninth bits are zeros
                                       //        clear RI0 and TI0 bits
   if (SYSCLK/BAUDRATE/2/256 < 1) {
      TH1 = -(SYSCLK/BAUDRATE/2);
      CKCON |=  0x08;                  // T1M = 1; SCA1:0 = xx
   } else if (SYSCLK/BAUDRATE/2/256 < 4) {
      TH1 = -(SYSCLK/BAUDRATE/2/4);
      CKCON &= ~0x0B;                  // T1M = 0; SCA1:0 = 01                  
      CKCON |=  0x01;
   } else if (SYSCLK/BAUDRATE/2/256 < 12) {
      TH1 = -(SYSCLK/BAUDRATE/2/12);
      CKCON &= ~0x0B;                  // T1M = 0; SCA1:0 = 00
   } else {
      TH1 = -(SYSCLK/BAUDRATE/2/48);
      CKCON &= ~0x0B;                  // T1M = 0; SCA1:0 = 10
      CKCON |=  0x02;
   }

   TL1 = TH1;                          // init Timer1
   TMOD &= ~0xf0;                      // TMOD: timer 1 in 8-bit autoreload
   TMOD |=  0x20;                       
   TR1 = 1;                            // START Timer1
   TI0 = 1;                            // Indicate TX0 ready



}


 void Timer3_Init (int counts)
{
   TMR3CN  = 0x00;                        // Stop Timer3; Clear TF3;
                                          // use SYSCLK/13 as timebase
   CKCON  &= ~0x60;                       // Timer3 clocked based on T3XCLK;

   TMR3RL  = -counts;                     // Init reload values
   TMR3    = 0xffff;                      // set to reload immediately
   ET3     = 1;                           // enable Timer3 interrupts
   TR3     = 1;                           // start Timer3
}


void Timer3_ISR (void) interrupt 5
{
   TF3H = 0;                              // clear Timer3 interrupt flag
   LED = ~LED;                            // change state of LED
}

//-----------------------------------------------------------------------------   
// ADC0_Init   
//-----------------------------------------------------------------------------   
//   
// Return Value : None   
// Parameters   : None   
//   
// Initialize the ADC to use the temperature sensor. (non-differential)   
//   
//-----------------------------------------------------------------------------   
void ADC0_Init (void)   
{   
   REF0CN |= 0x03;                     // Enable internal Vref   
   ADC0CN = 0x17;                      // Gain = 128, Bipolar mode   
   ADC0CF = 0x00;                      // Interrupts upon SINC3 filter output   
                                       // and uses internal VREF   
   
   ADC0CLK = (SYSCLK/MDCLK)-1;         // Generate MDCLK for modulator.   
                                       // Ideally MDCLK = 2.4576MHz   
   
   // Program decimation rate for desired OWR   
   ADC0DEC = ((signed long) MDCLK / (signed long) OWR /   
              (signed long) 128) - 1;   
   
   ADC0BUF = 0x00;                     // Turn off Input Buffers   
   ADC0MUX = 0x01;                     // Select AIN0 (+) y AIN1 (-)
   
   ADC0DAC = 0xBF;   //OFFSET POSITIVO MAXIMO 575mV 
   
   //ADC0MD = 0x81;                      // Start internal calibration   
   //while(AD0CALC != 1);                // Wait until calibration is complete   
   
   

   EIE1   |= 0x08;                     // Enable ADC0 Interrupts   
   ADC0MD  = 0x80;                     // Enable the ADC0 (IDLE Mode)   

   
}   
   
//-----------------------------------------------------------------------------   
// Interrupt Service Routines   
//-----------------------------------------------------------------------------   
   
//-----------------------------------------------------------------------------   
// ADC0_ISR   
//-----------------------------------------------------------------------------   
//   
// This ISR prints the result to the UART. The ISR is called after each ADC   
// conversion.   
//   
//-----------------------------------------------------------------------------   
void ADC0_ISR (void) interrupt 10   
{   
   
   static LONGDATA rawValue;   
   unsigned long mV;
   unsigned celda1,celda2,celda3,celda4;
      
   
   while(!AD0INT);                     // Wait till conversion complete
   AD0INT = 0;                         // Clear ADC0 conversion complete flag   
   
   if(ADC0MUX==0x01)
   {
   	      
   REF0CN |= 0x03;                     // Enable internal Vref   
   ADC0CN = 0x17;                      // Gain = 128, Bipolar mode   
   ADC0CF = 0x00;                      // Interrupts upon SINC3 filter output   
                                    // and uses internal VREF   
        
   ADC0BUF = 0x00;                     // Turn off Input Buffers   
   ADC0MUX = 0x23;                     // Select AIN0 (+) y AIN1 (-)
   
   ADC0MD = 0x82;

   rawValue.Byte[Byte3] = 0x00;   
   rawValue.Byte[Byte2] = (unsigned char)ADC0H;   
   rawValue.Byte[Byte1] = (unsigned char)ADC0M;   
   rawValue.Byte[Byte0] = (unsigned char)ADC0L;
   
   mV = rawValue.result / 6710;
   
   celda1=mV;  
   
   //printf("AIN 01 voltage:"); 
   }
   else if(ADC0MUX==0x23)
   {
   
      
   REF0CN |= 0x03;                     // Enable internal Vref   
   ADC0CN = 0x17;                      // Gain = 128, Bipolar mode   
   ADC0CF = 0x00;                      // Interrupts upon SINC3 filter output   
    
   
   ADC0BUF = 0x00;                     // Turn off Input Buffers   
   ADC0MUX = 0x45;                     // Select AIN0 (+) y AIN1 (-)
   
   ADC0MD = 0x82;

   rawValue.Byte[Byte3] = 0x00;   
   rawValue.Byte[Byte2] = (unsigned char)ADC0H;   
   rawValue.Byte[Byte1] = (unsigned char)ADC0M;   
   rawValue.Byte[Byte0] = (unsigned char)ADC0L; 

   mV = rawValue.result / 6710; 

   celda2=mV;
                                  
   //printf("AIN 23 voltage:"); 	
   }
   else if(ADC0MUX==0x45)
   {
   
      
   REF0CN |= 0x03;                     // Enable internal Vref   
   ADC0CN = 0x17;                      // Gain = 128, Bipolar mode   
   ADC0CF = 0x00;                      // Interrupts upon SINC3 filter output   
    
   
   ADC0BUF = 0x00;                     // Turn off Input Buffers   
   ADC0MUX = 0x67;                     // Select AIN0 (+) y AIN1 (-)
   
   ADC0MD = 0x82;

   rawValue.Byte[Byte3] = 0x00;   
   rawValue.Byte[Byte2] = (unsigned char)ADC0H;   
   rawValue.Byte[Byte1] = (unsigned char)ADC0M;   
   rawValue.Byte[Byte0] = (unsigned char)ADC0L; 

   mV = rawValue.result / 6710;
   
   celda3=mV; 
                                  
   //printf("AIN 45 voltage:"); 	
   }
   else
   {  
      
   REF0CN |= 0x03;                     // Enable internal Vref   
   ADC0CN = 0x17;                      // Gain = 128, Bipolar mode   
   ADC0CF = 0x00;                      // Interrupts upon SINC3 filter output   
    
   
   ADC0BUF = 0x00;                     // Turn off Input Buffers   
   ADC0MUX = 0x01;                     // Select AIN0 (+) y AIN1 (-)
   
   ADC0MD = 0x82;

   rawValue.Byte[Byte3] = 0x00;   
   rawValue.Byte[Byte2] = (unsigned char)ADC0H;   
   rawValue.Byte[Byte1] = (unsigned char)ADC0M;   
   rawValue.Byte[Byte0] = (unsigned char)ADC0L; 

   mV = rawValue.result / 6710; 

   celda4=mV;

   
                                  
   printf("%d %d %d %d ",celda1,celda2,celda3,celda4); 	
   }   
   
   // Copy the output value of the ADC   
   ///rawValue.Byte[Byte3] = 0x00;   
   ///rawValue.Byte[Byte2] = (unsigned char)ADC0H;   
   ///rawValue.Byte[Byte1] = (unsigned char)ADC0M;   
   ///rawValue.Byte[Byte0] = (unsigned char)ADC0L;   
   
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
   
   ///mV = rawValue.result / 6710;        // Because of bounds issues, this   
                                       // calculation has been manipulated as   
                                       // shown above   
                                       // (i.e. 2500 (VREF) * 2^24 (ADC result)   
                                       // is greater than 2^32)   

   
   //printf(" %4ld mV\n",mV);
   
       
   ///printf("%ld\n",mV); 
   

  


}   
   
//-----------------------------------------------------------------------------   
// End Of File   
//-----------------------------------------------------------------------------  



   
