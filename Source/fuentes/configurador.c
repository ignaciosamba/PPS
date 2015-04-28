/** Este archivo actua con la memoria flash y guarda las opciones configuracion
 * cada vez que hubo una configuracionnueva. Tambien saca las configuraciones de la
 * memoria y las carga en el programa en cada inicio del dispositivo.
 *  Tambien configura los registros de las interrupciones
**/

#include "headers.h"
#include "configurador.h"


int iniciar_ADC(void)
{
	
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

void iniciar_UART(void)
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


}

int cargar_configuracionFlash(void)
{
	return 0;
}

int guardar_configuracionFlash(void)
{
	return 0;
}
