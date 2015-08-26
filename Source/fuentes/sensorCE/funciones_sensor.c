#include "../headers.h"
#include "funciones_sensor.h"



void contar_RPM(void) // utiliza timer0
{
	static LONGDATA rawValue;
	unsigned long res = 0;
	short int i = 0;
	unsigned long rpm;
 	f_contRPM = false; 
	EA = 1;

	while(1)
	{
		ES0 = 1; // habilitar interrupcion de UART
		if (f_UART)
	    {
	    	EA = 0; // inhabilitar interrupciones globales
	    	f_UART = false;
	    	printf("STOP\n");
	    	break;
	    }
	    ES0 = 0;

		if(f_contRPM)
		{
			i++;
			f_contRPM = false; // se pone en falso la bandera del timer

			if(i > 15) // cada 15 interrupciones se llega a los 500 ms aproximadamente.
			{

				rawValue.Byte[Byte3] = 0x00;
				rawValue.Byte[Byte2] = 0x00;
				rawValue.Byte[Byte1] = (unsigned char)TH0;
				rawValue.Byte[Byte0] = (unsigned char)TL0;

				res = rawValue.result;

				rpm = res * 30; 
				// 4 eventos del timer0 son 1 vuelta del motor al tener este 4 aspas
				// cantidad de vueltas en 500 ms * 120 = vueltas por minuto.
				// (vueltas / 4) * 120 = rpm
				// vueltas * 30 = rpm

				// esto da una precision de 30 rpm. osea que cada resultado es +-30

				printf("%lu +-30 rpm\n", rpm);
			  	
				TH0 = 0;           // Resetear valor de timer0
				TL0 = 0;           
			  	i = 0;
		  	}
		}
	}

}