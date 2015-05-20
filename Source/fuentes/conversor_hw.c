#include "headers_hw.h"
#include "headers_logic.h"
#include "conversor.h"


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
