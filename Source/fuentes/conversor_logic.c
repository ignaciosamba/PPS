#include "headers_logic.h"
#include "conversor_logic.h"


int cont = 0;
short int posicion = 0;
short int dato_n;
unsigned short int num;



void cargar_buffer_single(struct shellstr *shell)
{
	dato_n = shell->args[0] - '0';
	// num = shell->args[5] * 10000 + shell->args[4] * 1000 + shell->args[3] * 100 + shell->args[2] * 10 + shell->args[1]; 
	num = shell->args[1] - '0';
	// printf("shell->args[1] == %c\n", shell->args[1]);

	shell->buffer_adc_count[dato_n] = num;

	shell->errn = 251;
}

void cargar_buffer_dif (struct shellstr *shell, char *dato)
{
	dato_n = *dato - '0';
	shell->buffer_adc_count [dato_n] = 2;

	shell->errn = 252;
}
