#include "headers.h"
#include "conversor.h"

int cont = 0;
short int posicion = 0;
short int dato_n;
int i ;



unsigned long convertir(void)
{
	static LONGDATA rawValue;
	unsigned long mV;
	
	while (!AD0INT);
	AD0INT = 0;
	//ADC0CN = 0X01;
	//printf("Entre al convertir\n");
	   // Copy the output value of the ADC
	rawValue.Byte[Byte3] = 0x00;
	rawValue.Byte[Byte2] = (unsigned char)ADC0H;
	rawValue.Byte[Byte1] = (unsigned char)ADC0M;
	rawValue.Byte[Byte0] = (unsigned char)ADC0L;

	//                           Vref (mV)
	//   measurement (mV) =   --------------- * result (bits)
	//                       (2^24)-1 (bits)
	//
	//   measurement (mV) =  result (bits) / ((2^24)-1 (bits) / Vref (mV))
	//
	//
	//   With a Vref (mV) of 2500:
	//
	//   measurement (mV) =  result (bits) / ((2^24)-1 / 2500)
	//
	//   measurement (mV) =  result (bits) / ((2^24)-1 / 2500)
	//
	//   measurement (mV) =  result (bits) / (16777215 / 2500)
	//
	//   measurement (mV) =  result (bits) / (6710)

	mV = rawValue.result / 6710;        // Because of bounds issues, this
	                                   // calculation has been manipulated as
	                                   // shown above
	                                   // (i.e. 2500 (VREF) * 2^24 (ADC result)
	                                   // is greater than 2^32)

	return mV;

}
/**
 * @brief por ahora no envia un carajo.. imprime en la UART nomas
 * @details [long description]
 */
void enviar_dato(unsigned long dato)
{
	//unsigned long dato2;
	//dato2=100;
	printf("voltaje: %8ld mV\n",dato);
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

void cargar_buffer_single(char dato)
{
		int i = 0;
		//printf("sdadasdasdas\n");
		// printf("cargue un 1 en la poscion: %c\n", dato );
		dato_n = dato - '0';
	 	printf("El valor numerico es: %hi\n",dato_n );
		//if(dato >= 0 && dato < 8)

		buffer_single [dato_n] = 1;
		for (i=0; i<8 ; i++)
		{
			printf("%hi\n", buffer_single[i]);
		}
}

 void cargar_buffer_dif (char dato)
 {
	printf("cargue un 1 en la poscion: %c\n", dato );
	dato_n = dato - '0';
	printf("El valor numerico es: %hi\n",dato_n );
	buffer_single [dato_n] = 2;
	for (i=0 ; i<8 ; i++)
		printf("%d\n", buffer_single[i] );

}

short int cambiar_pin()
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
		else if(buffer_single[posicion] == 2)
		{
			printf("Entre aca al else if. \n" );
			bandera_dif = 1;
			printf("la bandera es : %d\n",bandera_dif );
			posicion = posicion + 2;
			return posicion-2;
		}
		posicion++;
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