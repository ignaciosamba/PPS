#include "headers_logic.h"
#include "conversor_logic.h"


int cont = 0;
short int posicion = 0;
short int dato_n;
int i ;


/**
 * @brief por ahora no envia un carajo.. imprime en la UART nomas
 * @details [long description]
 */
void enviar_dato(unsigned long int *dato)
{
	//unsigned long dato2;
	//dato2=100;
	printf("voltaje: %u mV\n",*dato);
	// dato_convertido = dato;
	// f_enviar_dato = true;

	// if(ADC0MUX == 0x08)
	//    pin_actual = 0;
	// else if(ADC0MUX == 0x18)
	//    pin_actual = 1;
	// else if(ADC0MUX == 0x28)
	//    pin_actual = 2;
	// else if(ADC0MUX == 0x38)
	//    pin_actual = 3;
	// else if(ADC0MUX == 0x48)
	//    pin_actual = 4;
	// else if(ADC0MUX == 0x58)
	//    pin_actual = 5;
	// else if(ADC0MUX == 0x68)
	//    pin_actual = 6;
	// else if(ADC0MUX == 0x78)
	//    pin_actual = 7;
}

void cargar_buffer_single(struct shellstr *shell, char *dato)
{
		int i = 0;
		//printf("sdadasdasdas\n");
		// printf("cargue un 1 en la poscion: %c\n", dato );
		dato_n = *dato - '0';
	 	// printf("El valor numerico es: %hi\n",dato_n );
		//if(dato >= 0 && dato < 8)

		shell->buffer_single [dato_n] = 1;
		// for (i=0; i<8 ; i++)
		// {
		// 	printf("%hi\n", shell->buffer_single[i]);
		// }
		shell->errn = 201;
}

 void cargar_buffer_dif (struct shellstr *shell, char *dato)
 {
	// printf("cargue un 1 en la poscion: %c\n", *dato );
	dato_n = *dato - '0';
	// printf("El valor numerico es: %hi\n",dato_n );
	shell->buffer_single [dato_n] = 2;
	// for (i=0 ; i<8 ; i++)
	// 	printf("%d\n", shell->buffer_single[i] );

		shell->errn = 202;
}

short int cambiar_pin(struct shellstr *shell)
{
	while(1)
	{
		if (shell->posicion > 7)
		{
			shell->posicion = 0;
		}
		if(shell->buffer_single[shell->posicion] == 1)
		{
			shell->posicion++;
			return shell->posicion-1;
		}
		else if(shell->buffer_single[shell->posicion] == 2)
		{
			// printf("Entre aca al else if. \n" );
			bandera_dif = 1;
			// printf("la bandera es : %d\n",bandera_dif );
			shell->posicion = shell->posicion + 2;
			return shell->posicion-2;
		}
		shell->posicion++;
	}
}




/*void cambiar_pin (void)
{
	
	if(ADC0MUX == 0x78)
	{

	  		ADC0MUX = 0x08;
	  		cont = 0;
	  		printf("Entrada: %1d, ",cont);
	  		cont++;
	}
	else
	{
		  printf("Entrada: %1d, ",cont);
		  ADC0MUX = ((ADC0MUX & 0xf0) >> 4) | ((ADC0MUX & 0x0f) << 4); //Swapeo los 4 MSB con los 4 LSB para aumentar en uno el LSB
		  ADC0MUX++;
		  ADC0MUX = ((ADC0MUX & 0xf0) >> 4) | ((ADC0MUX & 0x0f) << 4); //Swapeo una vez mas asi me queda incrementado los 4 MSB y asi me movi de puerto. 
		  cont++;
	}
}*/