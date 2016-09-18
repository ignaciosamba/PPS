#include "headers.h"
#include "contador.h"

/**
 * @brief Devuelve el valor actual de Timer 0
 * @details Timer 0 esta configurado como contador de eventos. Esta funcion obtiene el valor actual de la cuenta y lo envia por la interfaz
 * 
 * @todo refactorizar para que utilice la funcion "enviar_dato" en vez de imprimir de pechaso
 */
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