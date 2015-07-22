#include "headers.h"
#include "contador.h"

void get_timer0(void)
{	  
	static LONGDATA rawValue;
	unsigned long res = 0;

	rawValue.Byte[Byte3] = 0x00;
	rawValue.Byte[Byte2] = 0x00;
	rawValue.Byte[Byte1] = (unsigned char)TH0;
	rawValue.Byte[Byte0] = (unsigned char)TL0;

	res = rawValue.result;

  	printf("Timer0 : %lu\n", res);
}

void get_timer2(void)
{	  
	static LONGDATA rawValue;
	unsigned long res = 0;

	rawValue.Byte[Byte3] = 0x00;
	rawValue.Byte[Byte2] = 0x00;
	rawValue.Byte[Byte1] = (unsigned char)TMR2H;
	rawValue.Byte[Byte0] = (unsigned char)TMR2L;

	res = rawValue.result;

  	printf("Timer2 : %lu\n", res);
}

// void get_PCA(void)
// {
// 	static LONGDATA rawValue;
// 	unsigned long res = 0;
	
// 	rawValue.Byte[Byte3] = 0x00;
// 	rawValue.Byte[Byte2] = 0x00;
// 	rawValue.Byte[Byte1] = (unsigned char)PCA0H;
// 	rawValue.Byte[Byte0] = (unsigned char)PCA0L;

// 	res = rawValue.result;

// 	printf("PCA : %lu\n", res);
   
// }