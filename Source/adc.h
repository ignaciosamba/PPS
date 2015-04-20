//-----------------------------------------------------------------------------
// Global CONSTANTS
//-----------------------------------------------------------------------------

#define SYSCLK       24500000          // SYSCLK frequency in Hz

#define MDCLK         2457600          // Modulator clock in Hz (ideal is
                                       // (2.4576 MHz)
#define OWR                20          // Desired Output Word Rate in Hz

#define BAUDRATE       115200          // Baud rate of UART in bps

sbit LED = P0^7;                       // LED='1' means ON
sbit SW2 = P1^0;                       // SW2='0' means switch pressed

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