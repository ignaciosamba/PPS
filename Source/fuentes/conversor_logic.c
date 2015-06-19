#include "headers_logic.h"
#include "conversor_logic.h"


int cont = 0;
short int posicion = 0;
short int dato_n;
int i ;



void cargar_buffer_single(struct shellstr *shell, char *dato)
{
	dato_n = *dato - '0';
	shell->buffer_adc [dato_n] = 1;

	shell->errn = 251;
}

void cargar_buffer_dif (struct shellstr *shell, char *dato)
{
	dato_n = *dato - '0';
	shell->buffer_adc [dato_n] = 2;

	shell->errn = 252;
}