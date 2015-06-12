/** Este archivo actua con la memoria flash y guarda las opciones configuracion
 * cada vez que hubo una configuracionnueva. Tambien saca las configuraciones de la
 * memoria y las carga en el programa en cada inicio del dispositivo.
 *  Tambien configura los registros de las interrupciones
**/
#include "headers_hw.h"
#include "headers_logic.h"
#include "configurador.h"



void seleccionar_puerto(unsigned short *puerto)
{
	switch (*puerto)
	{
		// ADC0CN = 0x01;
		case 0:
			printf("Puerto 0.0: \n");
			if (bandera_dif == 1)
			{
				bandera_dif = 0;
				ADC0CN |= 0x10;
				*puerto = 0x01;
				break;
			}
			else
			{
				*puerto = 0x08;
				break;
			}
		case 1:
			printf("Puerto 0.1: \n");
			*puerto = 0x18;
			break;
		case 2:
			printf("Puerto 0.2: \n");
			if (bandera_dif == 1)
			{
				bandera_dif = 0;
				ADC0CN |= 0x10;
				*puerto = 0x23;
				break;
			}
			else
			{
				*puerto = 0x28;
				break;
			}
		case 3: 
			printf("Puerto 0.3: \n");
			*puerto = 0x38;
			break;
		case 4:
			printf("Puerto 0.4: \n");
			if (bandera_dif == 1)
			{
				bandera_dif = 0;
				ADC0CN |= 0x10;
				*puerto = 0x45;
				break;
			}
			else
			{
				*puerto = 0x48;
				break;
			}
		case 5:
			*puerto = 0x58;
			printf("Puerto 0.5: \n");
			break;
		case 6:
			printf("Puerto 0.6: \n");
			if (bandera_dif == 1)
			{
				bandera_dif = 0;
				ADC0CN |= 0x10;
				*puerto = 0x67;
				break;
			}
			else
			{
				*puerto = 0x68;
				break;
			}
		case 7:
			printf("Puerto 0.7: \n");
			*puerto = 0x78;
			break;
		default:
			printf("ESTAMOS EN LA B \n" );
			break;
	}
	ADC0MUX = *puerto;
}

void iniciar_puertos (void)
{
   XBR0     = 0x01;                    // Habilitar UART en P0.4(TX) y P0.5(RX)                     
   XBR1     = 0x51;                    // Habilitar el crossbar, habilitar Timer0 y PCA
   P0MDOUT |= 0x10;                    // Habilitar UTX como push-pull output
   // P0MDIN |= 0x0C;                  // P0.3 y P0.4 tienen que ser entrada digital

}

void iniciar_sysclock (void)
{
   OSCICN |= 0x03;                     // configuracion del oscilador para la maxima frecuencia
   RSTSRC  = 0x04;                     // Enable missing clock detector
}


int iniciar_ADC(void)
{
	REF0CN |= 0x03;                     // Enable internal Vref
	ADC0CN = 0x00;                      // Gain = 1, Unipolar mode
	ADC0CF = 0x00;                      // Interrupts upon SINC3 filter output
	                                   // and uses internal VREF

	ADC0CLK = (SYSCLK/MDCLK)-1;         // Generate MDCLK for modulator.
	                                   // Ideally MDCLK = 2.4576MHz

	// Program decimation rate for desired OWR
	ADC0DEC = ((unsigned long) MDCLK / (unsigned long) OWR /
	          (unsigned long) 128) - 1;

	ADC0BUF = 0x00;                     // Turn off Input Buffers
	ADC0MUX = 0x08;                     // Select AIN0.2

	ADC0MD = 0x81;                      // Start internal calibration
	while(AD0CALC != 1);                // Wait until calibration is complete

	EIE1   |= 0x08;                     // Enable ADC0 Interrupts
	ADC0MD  = 0x80;                     // Enable the ADC0 (IDLE Mode)
	
	return 0;
}


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

void iniciar_timer0(void)
{
   TH0 = 0;           // Init Timer0 High register
   TL0 = 0;           // Init Timer0 Low register
   TMOD |= 0x25;                       // Timer0 in 16-bit mode, fuente externa                       // Timer0 interrupt enabled
   TCON |= 0x50;                        // Timer0 ON
}

void iniciar_timer2(void)
{
   TMR2CN |= 0x05;    // T2 en modo 16 bits, TR2 habilitado, clockeado por fuente externa
   TMR2L = 0;
   TMR2H = 0;
}
void iniciar_timer3(void)
{
   TMR3CN |= 0x05;    // T3 en modo 16 bits, TR3 habilitado, clockeado por fuente externa
   TMR3L = 0;
   TMR3H = 0;
}

void iniciar_PCA(void)
{
	PCA0CN = 0x00;                      // Stop counter; clear all flags
	PCA0MD = 0x06;                      // la fuente de eventos proviene de flancos de bajada en ECI
	PCA0H = 0;
	PCA0L = 0;
	PCA0CN = 0x40;                      // Habilitar PCA

}

void iniciar_osc_externo(void)
{
   OSCXCN |= 0x20; // seleccionar oscilador externo en modo CMOS Clock mode. Bits de control de frecuencia 0
}
