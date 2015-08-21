#include "headers.h"
#include "contador.h"

void get_timer0(void)
{	  
	static LONGDATA rawValue;
	unsigned long res = 0;

	rawValue.Byte[Byte3] = 0x00;
	rawValue.Byte[Byte2] = 0x00;
	rawValue.Byte[Byte1] = (unsigned char)TH0;
	rawValue.Byte[Byte0] = (unsigned char)TL0;

	res = rawValue.result;

  	printf("Timer0 : %lu\n", res);
}

void get_timer2(void)
{	  
	static LONGDATA rawValue;
	unsigned long res = 0;

	rawValue.Byte[Byte3] = 0x00;
	rawValue.Byte[Byte2] = 0x00;
	rawValue.Byte[Byte1] = (unsigned char)TMR2H;
	rawValue.Byte[Byte0] = (unsigned char)TMR2L;

	res = rawValue.result;

  	printf("Timer2 : %lu\n", res);
}

void contar_RPM(void)
{
	static LONGDATA rawValue;
	unsigned long res = 0;
	short int i = 0;
	EA = 1;

	while(1)
	{
		// ES0 = 1; // habilitar interrupcion de UART
		// if (f_UART)
	 //    {
	 //    	EA = 0; // inhabilitar interrupciones globales
	 //    	f_UART = false;
	 //    	printf("STOP\n");
	 //    	break;
	 //    }
	 //    ES0 = 0;
		// for(i = 0; i < 30; i++)
		// {
		// 	if(f_contRPM == true)
		// 		f_contRPM = false;
		// }

		if(f_contRPM)
		{
			f_contRPM = false; // se pone en falso la bandera del timer

			rawValue.Byte[Byte3] = 0x00;
			rawValue.Byte[Byte2] = 0x00;
			rawValue.Byte[Byte1] = (unsigned char)TMR3H;
			rawValue.Byte[Byte0] = (unsigned char)TMR3L;
	
			res = rawValue.result;
	
		  	printf("a veces arrrrrrrrmo cosass\n", res);
		}
	}

}

// void get_PCA(void)
// {
// 	static LONGDATA rawValue;
// 	unsigned long res = 0;
	
// 	rawValue.Byte[Byte3] = 0x00;
// 	rawValue.Byte[Byte2] = 0x00;
// 	rawValue.Byte[Byte1] = (unsigned char)PCA0H;
// 	rawValue.Byte[Byte0] = (unsigned char)PCA0L;

// 	res = rawValue.result;

// 	printf("PCA : %lu\n", res);
   
// }