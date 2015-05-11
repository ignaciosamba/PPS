#include "headers.h"
#include "interfaz.h"
#include "configurador.h"
#include "control.h"

int cont1 = 1;
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
	short int opcion;

	imprimir_menu();

		c_opcion = getchar();
		// printf("%c\n", c_opcion);
		/*if(c_opcion == '1')
			printf("YEAH\n");
		else printf("FUCK\n");
	*/
	switch(c_opcion)
	{
		case '1': 	imprimir_conf_ADC();
					c_opcion = getchar(); 
					switch (c_opcion)
					{
						case '1':	imprimir_conf_modo_single_ended();
									while (1)
									{
										c_opcion = getchar();
										while (getchar() != '\n');
										printf("esc\n");
										 // c_opcion = fgetc(stdin);
										if (c_opcion == 'r') 
											break;
										/*if (c_opcion > 7)
											printf("Valor invalido! Ingrese un numero del 0 al 7. \n");*/
										cargar_buffer_single(c_opcion);
									}
									// break;
									imprimir_conf_ADC();
									c_opcion = getchar();
									// break;
						case '3':	printf("\n");
									printf("Colocar la ganancia que se quiere aplicar,\n");
									printf("los valores admitidos son: \n");
									printf("1)x1  2)x2  3)x4  4)x8  5)x16  6)x32  7)x64  8)x128 .\n");
									c_opcion = getchar();
									switch (c_opcion)
									{
										case 1 : printf("Ganancia x1.\n"); ADC0CN = 0x00; break;
										case 2 : printf("Ganancia x2.\n"); ADC0CN = 0x01; break;
										case 3 : printf("Ganancia x4.\n"); ADC0CN = 0x02; break;
										case 4 : printf("Ganancia x8.\n"); ADC0CN = 0x03; break;
									}
						
					}
				   	break;
		case '2': imprimir_conf_modos(); break;
		case '3': imprimir_conf_tipoSerial(); break;
		default: printf("default!!\n");
		break;
	}

}