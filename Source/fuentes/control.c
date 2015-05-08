#include "headers.h"
#include "control.h"

#define TAM_SINGLE 8
int buffer_single [TAM_SINGLE];
int posicion;

int cargar_buffer_single(short int dato)
{
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