#include "headers.h"
#include "control.h"

#define TAM_SINGLE 8
//int buffer_single [TAM_SINGLE];
short int posicion = 0;
short int dato_n;


void cargar_buffer_single(char dato)
{
	// printf("sdadasdasdas\n");
	printf("cargue un 1 en la poscion: %c\n", dato );
	dato_n = dato - '0';
	printf("El valor numerico es: %hi\n",dato_n );
	buffer_single [dato_n] = 1; 
}

short int cambiar_pin()
{
	while(1)
	{
		if (posicion > 7)
		{
			posicion = 0;
		}
		if(buffer_single[posicion] == 1)
		{
			posicion++;
			return posicion-1;
		}
		posicion++;
	}
}