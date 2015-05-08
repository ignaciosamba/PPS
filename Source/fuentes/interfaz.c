#include "headers.h"
#include "interfaz.h"
#include "coonfigurador.h"
#include "control.h"


///MENU DE CONFIGURACION
void imprimir_menu(void)
{
	printf("\n Menú de configuracion\n");
	printf("1. Configuración de ADC\n");
	printf("2. Modos de transmision de datos\n");
	printf("3. Tipo de comunicacion serial\n");
	printf("4. Guardar la configuracion\n");
	printf("5. Salir e iniciar\n");
}

///CONFIGURACION DEL ADC

void imprimir_conf_ADC(void)
{
	printf("\n1. Configurar pins en modo single-ended\n");
	printf("2. Configurar pins en modo diferencial\n");
	printf("3. Configurar ganancia\n");
	printf("4. Volver al menu anterior\n");
}

void imprimir_conf_modo_single_ended(void)
{
	printf("\nIngresar los numeros de los pines separados por la tecla 'enter'\n");
	printf("Al terminar, ingrese la tecla 'r'\n");

}

void imprimir_conf_modo_diferencial(void)
{
	printf("\nIngresar, de a dos, los pares de los pines desados, separando los grupos con la tecla 'enter'\n");
	printf("Al terminar, ingrese la tecla 'r'\n");
}

///CONFIGURACION DE MODOS DE TRANSMISION DE DATOS

void imprimir_conf_modos(void)
{
	printf("\n1. Por peticion de dispositivo externo\n");
	printf("2. Flujo constante\n");
	printf("3. Por vencimiento de temporarizador\n");
	printf("4. Volver al menu anterior\n");
}

void imprimir_conf_tipoSerial(void)
{
	printf("\n1. RS232\n");
	printf("2. I2C (no implementado)\n");	
}


void correr_menu(void)
{
	char c_opcion;
	int opcion;
	char numeropuerto;

	imprimir_menu();

	c_opcion = getchar();
		// printf("%c\n", c_opcion);
/*		if(c_opcion == '1')
			printf("YEAH\n");
		else printf("FUCK\n");*/
	
	switch(c_opcion)
	{
		case '1': 
					imprimir_conf_ADC(); 
					c_opcion = getchar();
					switch (c_opcion)
					{
						case '1':
								imprimir_conf_modo_single_ended();
								numeropuerto = getchar();
								printf("numero de puerto: %c \n", numeropuerto );
							 	cargar_buffer_single(numeropuerto);
								break;
						default: printf("default\n");
					}
					break;
		case '2': imprimir_conf_modos(); break;
		case '3': imprimir_conf_tipoSerial(); break;
	
		case '5': printf("entre al 5 \n" ); iniciar_ADC(); break;
		default: printf("default!!\n");
		break;
	}

}