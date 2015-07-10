/**
 * @file conversor_logic.c
 * @author Sambataro, Ignacio; Mantovani, Luciano
 * @date 2015
 * @brief este archivo define el comportamiento de todas las funciones que intervienen en la logica del funcionamiento
 * del conversor analogico digital
 * @details [long description]
 */
#include "headers_logic.h"
#include "conversor_logic.h"


short int dato_n;
unsigned short int num;


/**
 * @brief carga uno de los pines del ADC en modo single-ended con un valor de 0 a 65536
 * @details el arreglo buffer_adc_count contiene los valores de todos los pines en todas las configuraciones
 * posibles. Esta funcion se encarga de cargar los valores desde el 0 al 7 de buffer_adc_count que corresponden a las configuraciones
 * de los pines en modo single-ended.
 * El valor con el que se cargen sera despues lo que determina la frecuencia de salida de los datos por el medio
 * de transmision. Mientras mas grande sea el valor, menor es la frecuencia. Si se carga con el valor 0, el pin
 * ingresado se deshabilita
 * 
 * @param shellstr se pasa la direccion de la estructura entera como parametro.
 * El campo args[0] da el valor del indice de buffer_adc_count. el resto de los argumentos de args dan el valor
 * con el que se cargara el elemento del array.
 * 
 * @warning esta funcion no tiene ningun efecto si el valor shell->args[0] es menor que 0 o mayor que 7
 */
void cargar_buffer_single(struct shellstr *shell)
{
	num = (unsigned)(atoi(shell->args + 1));

	dato_n = shell->args[0] - '0';
	if(dato_n > 0 && dato_n < 8)
	shell->buffer_adc_count[dato_n] = num;

	shell->errn = 251;
}

/**
 * @brief carga uno de los pines del ADC en modo diferencial con un valor de 0 a 65536
 * @details el arreglo buffer_adc_count contiene los valores de todos los pines en todas las configuraciones
 * posibles. Esta funcion se encarga de cargar los valores desde el 8 al 11 de buffer_adc_count que corresponden a las configuraciones
 * de los pines en modo diferencial.
 * El valor con el que se cargen sera despues lo que determina la frecuencia de salida de los datos por el medio
 * de transmision. Mientras mas grande sea el valor, menor es la frecuencia. Si se carga con el valor 0, el pin
 * ingresado se deshabilita
 * 
 * @param shellstr se pasa la direccion de la estructura entera como parametro.
 * El campo args[0] da el valor del indice de buffer_adc_count. Este valor corresponde a uno de los dos pines que seran
 * parte de la medicion por estar trabajando en modo diferencial. Solo se permite ingresar los pines 0,2,4 y 6; que 
 * corresponden a la medicion de los pines 0-1; 2-3; 4-5; y 5-6 respectivamente.
 * con el que se cargara el elemento del array.
 * 
 * @warning esta funcion no tiene ningun efecto si el valor shell->args[0] es impar, menor que 0 o mayor que 6
 */
void cargar_buffer_dif (struct shellstr *shell)
{
	num = (unsigned)(atoi(shell->args + 1));

	switch(shell->args[0])
	{
		case '0': dato_n = 8; break;
		case '2': dato_n = 9; break;
		case '4': dato_n = 10; break;
		case '6': dato_n = 11; break;
		default: shell->errn = 406; return; 
	}

	shell->buffer_adc_count[dato_n] = num;

	shell->errn = 252;
}
