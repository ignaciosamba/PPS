#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char byte;
#define ARRAYSIZE 8
#define MAXSIZE 50
#define TAM_SINGLE 			 8 			//define para tamaño de buffer! 

typedef enum { false, true } bool;

// /*variables globales*/
// unsigned long dato_convertido;
// unsigned short pin_actual;


/*FLAGS globales*/

extern bool f_dato_convertido;
extern int buffer_single [TAM_SINGLE];
extern short int bandera_dif;


struct shellstr /// estructura para majejar la entrada de operaciones en la interfaz MML 
{   
	///cantidad de argumentos de la entrada
	char n_args; 
	///la entrada completa
	char *entrada; 
	///comando de la entrada
	char *comando; 
	///arreglo de argumentos. maximo 4
	char *args[4]; 

	///array para el conversor
	char *buffer_single;  
	///posicion dentro del array 
	short int posicion;				
};