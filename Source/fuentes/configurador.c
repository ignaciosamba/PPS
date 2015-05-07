/** Este archivo actua con la memoria flash y guarda las opciones configuracion
 * cada vez que hubo una configuracionnueva. Tambien saca las configuraciones de la
 * memoria y las carga en el programa en cada inicio del dispositivo.
 *  Tambien configura los registros de las interrupciones
**/

#include "headers.h"
#include "configurador.h"



void iniciar_puertos (void)
{
   P0MDOUT |= 0x10;                    // Enable UTX as push-pull output
   XBR0     = 0x01;                    // Enable UART on P0.4(TX) and P0.5(RX)                     
   XBR1     = 0x40;                    // Enable crossbar and weak pull-ups
}

void iniciar_sysclock (void)
{
   OSCICN |= 0x03;                     // configuracion del oscilador para la maxima frecuencia
   RSTSRC  = 0x04;                     // Enable missing clock detector
}

/**
void cambiarpuerto(puerto)
{
	pasar de decimal a binario con switch.
	ADC0MUX = puerto;
}
**/

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
	ADC0MUX = 0x08;                     // Select AIN0.0

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

int iniciar_interrupciones(void)
{
	
	return 0;
}

int iniciar_FLASH(void)
{
	
	return 0;
}

int cargar_configuracionFlash(void)
{
	return 0;
}

int guardar_configuracionFlash(void)
{
	return 0;
}

void configurar_single_ended (char puerto)
{

}
