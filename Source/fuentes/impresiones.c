#include "headers.h"
#include "impresiones.h"


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

void imprimir_conf_ganancia(void)
{
	printf("\n");
	printf("Colocar la ganancia que se quiere aplicar,\n");
	printf("los valores admitidos son: \n");
	printf("1)x1  2)x2  3)x4  4)x8  5)x16  6)x32  7)x64  8)x128 .\n");
}