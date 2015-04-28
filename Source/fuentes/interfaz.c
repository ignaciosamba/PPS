#include "headers.h"


void imprimir_menu(void)
{
	printf("\n Menú de configuracion\n");
	printf("1. Configuración de ADC\n");
	printf("2. Modos de transmision de datos\n");
	printf("3. Tipo de comunicacion serial\n");
	printf("4. Guardar la configuracion\n");
	printf("5. Salir\n");
}

void imprimir_conf_ADC(void)
{
	printf("\n1. Configurar pins en modo single-ended\n");
	printf("2. Configurar pins en modo diferencial\n");
	printf("3. Configurar ganancia\n");
}

void imprimir_conf_modos(void)
{
	printf("\n1. Por peticion de dispositivo externo\n");
	printf("2. Flujo constante\n");
	printf("3. Por vencimiento de temporarizador\n");
}

void imprimir_conf_tipoSerial(void)
{
	printf("\n1. RS232\n");
	printf("2. I2C\n");	
}


void correr_menu(void)
{
	char c_opcion;
	int opcion;

	imprimir_menu();

		c_opcion = getchar();
		// printf("%c\n", c_opcion);
/*		if(c_opcion == '1')
			printf("YEAH\n");
		else printf("FUCK\n");*/
	
	switch(c_opcion)
	{
		case '1': imprimir_conf_ADC(); break;
		case '2': imprimir_conf_modos(); break;
		case '3': imprimir_conf_tipoSerial(); break;
		default: printf("default!!\n");
		break;
	}

}