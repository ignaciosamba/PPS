#include "headers.h"
#include "interfaz.h"
#include "configurador.h"
#include "conversor.h"
#include "impresiones.h"

int cont1 = 1;



void correr_menu(void)
{
	char c_opcion;
	short int opcion = 1;

	while(opcion==1)
	{
		imprimir_menu();

		c_opcion = getchar();
		while (getchar() != '\n');

		// printf("%c\n", c_opcion);
		switch(c_opcion)
		{
			case '1': 	
						imprimir_conf_ADC();
						c_opcion = getchar(); 
						while (getchar() != '\n');
						switch (c_opcion)
						{
							case '1':	conf_single_ended(); break;
							case '3':	conf_ganancia(); break;
							
						}
			case '2': imprimir_conf_modos(); break;
			case '3': imprimir_conf_tipoSerial(); break;
			case '4': break;
			case '5': opcion = 0; break;
			default: printf("default!!\n");
			break;
		}

	}
}

void conf_single_ended(void)
{
	char c_opcion;
	imprimir_conf_modo_single_ended();
	while (1)
	{
		c_opcion = getchar();
		while (getchar() != '\n');
		// printf("esc\n");
		if (c_opcion == 'r') 
				break;
		/*if (c_opcion > 7)
			printf("Valor invalido! Ingrese un numero del 0 al 7. \n");*/
		cargar_buffer_single(c_opcion);
	}

}

void conf_ganancia(void)
{
	char c_opcion;

	imprimir_conf_ganancia();
	c_opcion = getchar();
	switch (c_opcion)
	{
		case 1 : printf("Ganancia x1.\n"); ADC0CN = 0x00; break;
		case 2 : printf("Ganancia x2.\n"); ADC0CN = 0x01; break;
		case 3 : printf("Ganancia x4.\n"); ADC0CN = 0x02; break;
		case 4 : printf("Ganancia x8.\n"); ADC0CN = 0x03; break;
	}
}

