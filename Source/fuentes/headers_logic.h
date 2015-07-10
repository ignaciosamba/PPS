/**
 * @file headers_logic.h
 * @author Sambataro, Ignacio; Mantovani, Luciano
 * @date 2015
 * @brief establece las librerias y define las variables que caen dentro del campo de la logica del codigo, sin\
 * ningun aspecto correspondiente al hardware. 
 * @details define algunos nombres, declara variables globales, y declara la estructura shellstr, que es parametro
 * en casi todas las funciones del programa
 */
#include <stdio.h>
#include <stdlib.h>

typedef char byte;
#define ARRAYSIZE 8
#define MAXSIZE 50
#define TAM_SINGLE 12 			//define para tamaño de buffer! 


#define TAM_COMANDO 3
#define MAX_ARGS 8

typedef enum { false, true } bool;

// /*variables globales*/
// unsigned long dato_convertido;
// unsigned short pin_actual;


///bandera de dato convertido
extern bool f_dato_convertido;
// extern bool f_UART;

/// estructura general del programa que contiene los elementos principales del mismo. Al estar organizado en forma de estructura se facilita el pase de parametros, y mas aun si se inicializa como puntero a estructura
struct shellstr  
{   
	///cantidad de argumentos de la entrada
	char n_args; 
	///la entrada completa
	char entrada; 
	///comando de la entrada
	char comando[TAM_COMANDO]; 
	// char *comando; 
	
	///arreglo de argumentos. maximo 8
	char args[MAX_ARGS]; 
	// char *args; 

	///array variable para el conversor, al iniciar el adc, es igual a buffer_adc_count
	unsigned short int buffer_adc[TAM_SINGLE];  

	///array estatico que se carga para dar una frecuencia a las salidas del adc con buffer_adc
	unsigned short int buffer_adc_count[TAM_SINGLE];  
	
	///posicion dentro del array 
	short int posicion;				

	///numero de error de error
	short int errn;

	///bandera de habilitacion de configuracion
	char stop_conf;

	///variable auxiliar para el indexado de buffer_adc
	char var;
};