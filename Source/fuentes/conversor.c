#include "headers.h"
#include "conversor.h"

int cont = 0;
short int posicion = 0;
char dato_n;


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
void enviar_dato(unsigned long int *dato)
{
	//unsigned long dato2;
	//dato2=100;
	printf("voltaje: %8ld mV\n",*dato);
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

char cargar_buffer_single(char *dato)
{
	switch(*dato)
	{
		case '0': return (*dato | 0x01);
		case '1': return (*dato | 0x02);
		case '2': return (*dato | 0x04);
		case '3': return (*dato | 0x08);
		case '4': return (*dato | 0x10);
		case '5': return (*dato | 0x20);
		case '6': return (*dato | 0x40);
		case '7': return (*dato | 0x80);

		default: return *dato;
	}


		// sbit buffer_single_destpin;
		// // int i = 0;
		// //printf("sdadasdasdas\n");
		// // printf("cargue un 1 en la poscion: %c\n", dato );
		// dato_n = dato - '0';

	 // 	// printf("El valor numerico es: %hi\n",dato_n );
		// //if(dato >= 0 && dato < 8)
		// buffer_single_destpin = buffer_single ^ dato_n;
		// buffer_single_destpin = 1;
		// // for (i=0; i<8 ; i++)
		// // {
		// // 	printf("%hi\n", buffer_single[i]);
		// // }
}

short int cambiar_pin()
{
	while(1)
	{
		if (posicion > 7)
		{
			posicion = 0;
		}
		if(buffer_single ^ posicion == 1)
		{
			posicion++;
			return posicion-1;
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