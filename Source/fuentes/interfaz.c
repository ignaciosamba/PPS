#include "headers_logic.h"
#include "interfaz.h"
#include "configurador.h"
#include "conversor.h"
#include "impresiones.h"




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
							case '2':	conf_dif(); break;
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
		// FLASH_Write(dest, &c_opcion, numbytes);
	}

}

void conf_dif(void)
{
	char c_opcion;

	imprimir_conf_modo_diferencial();
	while (1)
	{
		c_opcion = getchar();
		while (getchar() != '\n');
		// printf("esc\n");
		if (c_opcion == 'r') 
			break;
		/*if (c_opcion > 7)
			printf("Valor invalido! Ingrese un numero del 0 al 7. \n");*/
		cargar_buffer_dif(c_opcion);
		// FLASH_Write(dest, &c_opcion, numbytes);
	}

}


void conf_ganancia(void)
{
	char c_opcion;
	imprimir_conf_ganancia();
	c_opcion = getchar();
	switch (c_opcion)
	{
		case '1' : printf("Ganancia x1.\n"); ADC0CN = 0x00; break;
		case '2' : printf("Ganancia x2.\n"); ADC0CN = 0x01; break;
		case '3' : printf("Ganancia x4.\n"); ADC0CN = 0x02; break;
		case '4' : printf("Ganancia x8.\n"); ADC0CN = 0x03; break;
		case '5' : printf("Ganancia x16.\n"); ADC0CN = 0x04; break;
		case '6' : printf("Ganancia x32.\n"); ADC0CN = 0x05; break;
		case '7' : printf("Ganancia x64.\n"); ADC0CN = 0x06; break;
		case '8' : printf("Ganancia x128.\n"); ADC0CN = 0x07; break;
	}
}



