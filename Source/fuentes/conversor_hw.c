/**
 * @file conversor_hw.c
 * @author Sambataro, Ignacio; Mantovani, Luciano
 * @date 2015
 * @brief este archivo define el comportamiento de todas las funciones que intervienen en la logica a nivel de
 * registro del conversor analogico digital.
 */

#include "headers_hw.h"
#include "headers_logic.h"
#include "conversor_hw.h"

/**
 * @brief Esta funcion obtiene un valor de los registros ADC0H, ADC0M, y ADC0L. Que corresponden al valor de la
 * conversion actual.
 * @details El valor de conversion tiene un total de 24 bits, y esta repartido en 3 registros de 8 bits.
 * Para obtener este valor es necesario hacer un calculo teniendo en cuenta la tension de referencia con la que
 * se trabaja.
 * @return Devuelve el valor obtenido en los registros
 */
unsigned long convertir(void)
{
	static LONGDATA rawValue;
	unsigned long mV;
	
   // Copiar el valor del registro de conversion del adc en una variable local
	rawValue.Byte[Byte3] = 0x00;
	rawValue.Byte[Byte2] = (unsigned char)ADC0H;
	rawValue.Byte[Byte1] = (unsigned char)ADC0M;
	rawValue.Byte[Byte0] = (unsigned char)ADC0L;

	//                           Vref (mV)
	//   medicion (mV) =   --------------- * result (bits)
	//                       (2^24)-1 (bits)
	//
	//   medicion (mV) =  result (bits) / ((2^24)-1 (bits) / Vref (mV))
	//
	//
	//   Con un voltaje de referencia de 2.5 V:
	//
	//   medicion (mV) =  result (bits) / ((2^24)-1 / 2500)
	//
	//   medicion (mV) =  result (bits) / ((2^24)-1 / 2500)
	//
	//   medicion (mV) =  result (bits) / (16777215 / 2500)
	//
	//   medicion (mV) =  result (bits) / (6710)

	// se calcula el voltaje medido segun el voltaje de referencia
	mV = rawValue.result / 6710;        

	return mV;

}

/**
 * @brief Configura la ganancia a la entrada del ADC.
 * @details La ganancia determina la magnitud de la señal a medir. El valor de amplificacion puede ser de 
 * un factor de 2 a 128
 * 
 * @param shellstr se pasa la direccion de la estructura entera como parametro. El valor de args[0] determina
 * el factor por el que se potencia a 2 para obtener la ganancia.
 * @return devuelve la misma estructura
 */
struct shellstr *conf_ganancia(struct shellstr *shell)
{	
	ADC0MD = 0x80;
	switch (shell->args[0])
	{
		case '0': ADC0CN = (ADC0CN & 0xF0) + 0x00; break;
		case '1': ADC0CN = (ADC0CN & 0xF0) + 0x01; break;
		case '2': ADC0CN = (ADC0CN & 0xF0) + 0x02; break;
		case '3': ADC0CN = (ADC0CN & 0xF0) + 0x03; break;
		case '4': ADC0CN = (ADC0CN & 0xF0) + 0x04; break;
		case '5': ADC0CN = (ADC0CN & 0xF0) + 0x05; break;
		case '6': ADC0CN = (ADC0CN & 0xF0) + 0x06; break;
		case '7': ADC0CN = (ADC0CN & 0xF0) + 0x07; break;
		default: shell->errn = 407; ADC0MD = 0x83; return shell;
	}
	ADC0MD = 0x83;
	shell->errn = 253;
	return shell;

}


/**
 * @brief Cambia el pin actual medido al siguiente.
 * @details Cada vez que se llama esta funcion, se analiza el estado actual del registro ADC0MUX, y segun su 
 * valor, se calcula el valor siguiente. Esta hecha de forma que recorra todos los pines en todos sus modos
 * posibles en forma de escalera; de forma que si se llama en un ciclo infinito, recorreria todos los pines
 * en todas sus configuraciones, con una frecuencia igual para cada pin.
 */
void cambiar_pin()
{
	ADC0MD = 0x80; // ADC en modo idle
	if((ADC0MUX & 0x0F) == 0x08) // si los 4 LSB de ADC0MUX son 8, estamos en modo single ended
	{
		if(ADC0MUX == 0x78) // si estamos en el ultimo pin del modo single ended, hay que pasar a modo diferencial
		{
			ADC0CN |= 0x10; // se habilita el modo diferencial
			ADC0MUX = 0x01; // se setean los pines 0 y 1 en modo diferencial
			ADC0MD = 0x83; // ADC en modo conversion continua
			return;
		}
		ADC0MUX = ADC0MUX + 0x10; // se cambia al pin siguiente
		ADC0MD = 0x83; // ADC en modo conversion continua
		return;
	}
	if((ADC0MUX & 0x0F) < 0x08)// si los 4 LSB de ADC0MUX son menores a 8, estamos en modo diferencial
	{
		if(ADC0MUX == 0x67) // si estamos en el ultimo par de pines del modo diferencial, hay que pasar a modo single-ended.
		{
			ADC0CN &= ~0x10; // se habilita el modo bipolar
			ADC0MUX = 0x08; // se setea el pin 0 en modo single-ended
			ADC0MD = 0x83; // ADC en modo conversion continua
			return;
		}		
		ADC0MUX = ADC0MUX + 0x22; // se cambia al siguiente par de pines
		ADC0MD = 0x83; // ADC en modo conversion continua
		return;
	}
}

/**
 * @brief Envia datos por la interfaz serial
 * @details el formato de envio es: MODO,PIN,VALOR. Donde el modo puede ser SE o DF, siendo single-ended o 
 * diferencial, respectivamente; el pin es el pin donde se midio, en el caso que sea diferencial, se le debe 
 * sumar 1 al pin mostrado para tener los pines donde se midio; y el valor es el valor medido.
 * 
 * @param long El dato a enviar
 */
void enviar_dato(unsigned long int *dato)
{
	char num_pin;
	num_pin = (char)ADC0MUX;

	if((num_pin & 0x0F) == 0x08)
	{
		printf("SE,%c,%lu\n", (num_pin >> 4) + '0',*dato);
	}
	else if((num_pin & 0x0F) < 0x08)
	{
		printf("DF,%c,%lu\n", (num_pin >> 4) + '0',*dato);
	}
}

/**
 * @brief Analiza el buffer de pines para determinar si el envio esta o no habilitado
 * @details Esta funcion se encarga de verificar si el pin medido esta habilitado para el envio o no.
 * Esta funcion fue hecha para trabajar en conjunto con la funcion cambiar_pin(). La idea es que se haga un
 * barrido constante de todos los pines en todos sus modos, pero que se envien solo los que deban enviarse.
 * La informacion de si se envia o no esta en los buffers "buffer_adc_count" y "buffer_adc". El primero contiene
 * los valores iniciales de cada pin en cada modo, y el segundo contiene los valores actuales. Cada vez que se 
 * hace un llamado a esta funcion, el los valores de buffer_adc se decrementan en 1. Cuando un elemento el array
 * llega a 1, esta habilitado para el envio. Si un elemento tiene valor 0, el pin correspondiente esta deshabilitado.
 * @return devuelve true si el pin actual esta habilitado para enviar, 0 si no esta habilitado.
 */
char analizar_buffer(struct shellstr *shell)
{
	char idx;
	char lsb, msb;
	lsb = (char)(ADC0MUX & 0x0F);
	msb = (char)(ADC0MUX >> 4); 

	//si el modulo de los 4LSB de ADC0MUX con 8 es mayor a 0, estamos en la parte diferencial de buffer_adc
	if((lsb % 8) > 0)
		shell->var++;
	else shell->var = 0; //si no, estamos en la parte single ended.

	// se restan ambos grupos de 4 de bits de ADC0MUX, se le suma 8, y se le suma la variable auxiliar
	// que es mayor a 0 unicamente cuando es necesario que el indice recorra la parte diferencial 
	idx = msb - lsb + 8 + shell->var;
 	
 	//con esta operacion, idx recorre todos los indices del buffer, teniendo en cuenta el valor de ADC0MUX
 	if(idx < 12)
 	{
		if(shell->buffer_adc [idx] == 0)
		{
			return 0;
		}
		if(shell->buffer_adc [idx] == 1)
		{
			shell->buffer_adc [idx] = shell->buffer_adc_count[idx];
			return 1;
		}
		if(shell->buffer_adc [idx] > 1)
		{
			shell->buffer_adc[idx]--;
			return 0;
		}
	}	
	else
	{
		printf("se detono todo\n");
		printf("idx: %i\n", (int)idx);
		printf("ADC0MUX: 0x%x\n", (char)ADC0MUX);
		printf("var: %i\n", (int)shell->var);
		return -1;
	}
	return 0;
}