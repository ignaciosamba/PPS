#include "headers.h"
#include "control.h"

#define TAM_SINGLE 8
//int buffer_single [TAM_SINGLE];
int posicion;


void cargar_buffer_single(char dato)
{
	//printf("sdadasdasdas\n");
	printf("cargue un 1 en la poscion: %c\n", dato );
	buffer_single [dato] = 1; 
}

int cambiar_pin()
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