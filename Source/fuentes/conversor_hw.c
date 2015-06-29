#include "headers_hw.h"
#include "headers_logic.h"
#include "conversor_hw.h"


unsigned long convertir(void)
{
	static LONGDATA rawValue;
	unsigned long mV;
	
	// while (!AD0INT);
	// AD0INT = 0;
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


struct shellstr *conf_ganancia(struct shellstr *shell)
{	
	ADC0MD = 0x80;
	switch (shell->args[0])
	{
		case '0': ADC0CN = (ADC0CN & 0xF0) + 0x00; break;
		case '1': ADC0CN = (ADC0CN & 0xF0) + 0x01; break;
		case '2': ADC0CN = (ADC0CN & 0xF0) + 0x02; break;
		case '3': ADC0CN = (ADC0CN & 0xF0) + 0x03; break;
		case '4': ADC0CN = (ADC0CN & 0xF0) + 0x04; break;
		case '5': ADC0CN = (ADC0CN & 0xF0) + 0x05; break;
		case '6': ADC0CN = (ADC0CN & 0xF0) + 0x06; break;
		case '7': ADC0CN = (ADC0CN & 0xF0) + 0x07; break;
		default: shell->errn = 407; ADC0MD = 0x83; return shell;
	}
	ADC0MD = 0x83;
	shell->errn = 253;
	return shell;

}
/**
 * @brief recorre todas las opciones de los pines tanto single ended como diferencial
 * @details [long description]
 * 
 * @param f [description]
 */
void cambiar_pin()
{
	ADC0MD = 0x80;
	if((ADC0MUX & 0x0F) == 0x08)
	{
		if(ADC0MUX == 0x78)
		{
			ADC0CN |= 0x10;
			ADC0MUX = 0x01;
			ADC0MD = 0x83;
			return;
		}
		// ADC0CN &= ~0x10;
		ADC0MUX = ADC0MUX + 0x10;
		ADC0MD = 0x83;
		return;
	}
	if((ADC0MUX & 0x0F) < 0x08)
	{
		if(ADC0MUX == 0x67)
		{
			ADC0CN &= ~0x10;
			ADC0MUX = 0x08;
			ADC0MD = 0x83;
			return;
		}		
		// ADC0CN |= 0x10;
		ADC0MUX = ADC0MUX + 0x22;
		ADC0MD = 0x83;
		return;
	}
}

/**
 * @brief envia datos por la uart
 * @details [long description]
 * 
 * @param long [description]
 */
void enviar_dato(unsigned long int *dato)
{
	char num_pin;
	num_pin = (char)ADC0MUX;

	if((num_pin & 0x0F) == 0x08)
	{
		printf("SE,%c,%lu\n", (num_pin >> 4) + '0',*dato);
	}
	else if((num_pin & 0x0F) < 0x08)
	{
		printf("DF,%c,%lu\n", (num_pin & 0x0F) + '0',*dato);
	}
}

/**
 * @brief devuelve 1 si el pin actual tiene el envio habilitado
 * @details [long description]
 * @return [description]
 */
char analizar_buffer(struct shellstr *shell)
{
	char idx;
	char lsb, msb;
	lsb = (char)(ADC0MUX & 0x0F);
	msb = (char)(ADC0MUX >> 4); 

	//si el modulo de los 4LSB de ADC0MUX con 8 es mayor a 0, estamos en la parte diferencial de buffer_adc
	if((lsb % 8) > 0)
		shell->var++;
	else shell->var = 0; //si no, estamos en la parte single ended.

	// se restan ambos grupos de 4 de bits de ADC0MUX, se le suma 8, y se le suma la variable auxiliar
	// que es mayor a 0 unicamente cuando es necesario que el indice recorra la parte diferencial 
	idx = msb - lsb + 8 + shell->var;
 	
 	//con esta operacion, idx recorre todos los indices del buffer, teniendo en cuenta el valor de ADC0MUX
 	if(idx < 12)
 	{
		if(shell->buffer_adc [idx] == 0)
		{
			return 0;
		}
		if(shell->buffer_adc [idx] == 1)
		{
			shell->buffer_adc [idx] = shell->buffer_adc_count[idx];
			return 1;
		}
		if(shell->buffer_adc [idx] > 1)
		{
			shell->buffer_adc[idx]--;
			return 0;
		}
	}	
	else
	{
		printf("se detono todo\n");
		printf("idx: %i\n", (int)idx);
		printf("ADC0MUX: 0x%x\n", (char)ADC0MUX);
		printf("var: %i\n", (int)shell->var);
		return -1;
	}
	return 0;
}