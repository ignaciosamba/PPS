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
	switch (shell->args[0])
	{
		case '0': printf("Ganancia x1.\n"); ADC0CN = 0x00; break;
		case '1': printf("Ganancia x2.\n"); ADC0CN = 0x01; break;
		case '2': printf("Ganancia x4.\n"); ADC0CN = 0x02; break;
		case '3': printf("Ganancia x8.\n"); ADC0CN = 0x03; break;
		case '4': printf("Ganancia x16.\n"); ADC0CN = 0x04; break;
		case '5': printf("Ganancia x32.\n"); ADC0CN = 0x05; break;
		case '6': printf("Ganancia x64.\n"); ADC0CN = 0x06; break;
		case '7': printf("Ganancia x128.\n"); ADC0CN = 0x07; break;
		default: shell->errn = 407; return shell;
	}
	shell->errn = 253;
	return shell;

}

void cambiar_pin()
{
	if((ADC0MUX & 0x0F) == 0x08)
	{
		if(ADC0MUX == 0x78)
		{
			ADC0CN |= 0x10;
			ADC0MUX = 0x10;
			return;
		}
		ADC0CN &= ~0x10;
		ADC0MUX = ADC0MUX + 0x10;
		return;
	}
	if((ADC0MUX & 0x0F) < 0x08)
	{
		if(ADC0MUX == 0x76)
		{
			ADC0CN &= ~0x10;
			ADC0MUX = 0x08;
			return;
		}		
		ADC0CN |= 0x10;
		ADC0MUX = ADC0MUX + 0x22;
		return;
	}
}

/**
 * @brief envia datos por la uart
 * @details [long description]
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