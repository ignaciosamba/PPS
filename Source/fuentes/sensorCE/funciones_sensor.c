#include "../headers.h"
#include "funciones_sensor.h"

#define V_FASE_1 42200
#define V_FASE_2 42100
#define V_ARRANQUE 33264
#define V_ESTABLE 36000


short int velocidad = V_ESTABLE;

void contar_RPM(void) // utiliza timer0
{
	static LONGDATA rawValue;
	unsigned long res = 0;
	short int i = 0;
	unsigned long rpm;
 	f_contRPM = false; 
	EA = 1;

	while(1)
	{
		ES0 = 1; // habilitar interrupcion de UART
		if (f_UART)
	    {
	    	EA = 0; // inhabilitar interrupciones globales
	    	f_UART = false;
	    	printf("STOP\n");
	    	break;
	    }
	    ES0 = 0;

		if(f_contRPM)
		{
			i++;
			f_contRPM = false; // se pone en falso la bandera del timer

			if(i > 15) // cada 15 interrupciones se llega a los 500 ms aproximadamente.
			{

				rawValue.Byte[Byte3] = 0x00;
				rawValue.Byte[Byte2] = 0x00;
				rawValue.Byte[Byte1] = (unsigned char)TH0;
				rawValue.Byte[Byte0] = (unsigned char)TL0;

				res = rawValue.result;

				rpm = res * 30; 
				// 4 eventos del timer0 son 1 vuelta del motor al tener este 4 aspas
				// cantidad de vueltas en 500 ms * 120 = vueltas por minuto.
				// (vueltas / 4) * 120 = rpm
				// vueltas * 30 = rpm

				// esto da una precision de 30 rpm. osea que cada resultado es +-30

				printf("%lu +-30 rpm\n", rpm);
				control_RPM(rpm,V_ESTABLE);
			  	
				TH0 = 0;           // Resetear valor de timer0
				TL0 = 0;           
			  	i = 0;
		  	}
		}
	}

}
/**
 * @brief agrega una histeresis al funcionamiento del motor que evita el desvio de las RPM
 * @details [long description]
 */
void control_RPM(short int rpm_real, short int rpm_ideal)
{
	if(rpm_real > rpm_ideal + 50) // si las rpm son muy altas
	{
		set_Pwm(velocidad - 100); // se sube la velocidad relativa
		printf("se controlo para que vaya mas despacio\n");
	}

	if(rpm_real < rpm_ideal - 50) // si las rpm son muy bajas
	{
		set_Pwm(velocidad + 100); // se baja la velocidad relativa
		printf("se controlo para que vaya mas rapido\n");
	}
}

/**
 * @brief arranca el motor usando el pwm de la placa
 * @details [long description]
 */
void arrancar_motor(void) 
{
	printf("\nFase 1...\n");
	set_Pwm(V_FASE_1);
	delay(600);
	printf("Fase 2...\n");
	set_Pwm(V_FASE_2);
	delay(600);
	printf("Arranque...\n");
	set_Pwm(V_ARRANQUE);
	delay(600);
	printf("Nivel estable\n");
	set_Pwm(V_ESTABLE);
}

/**
 * @brief cambia el ciclo de trabajo del PWM
 * @details con esta funcion se puede cambiar el ciclo de trabajo del pwm usando el registro PCA0CPL0 del PCA.
 * Cambia segun la funcion
 * 
 *  cdt = (65536 - PCA0CPn) / 65536
 * 
 * @param int [description]
 */
void set_Pwm(unsigned int num)
{
	EIE1 |= 0x10;                       // Enable PCA interrupts
	EA = 1;

	while(CCF0 != 0);       // espera que termine el ciclo de trabajo

	// luego setea los valores
	PCA0CPL0 = (num & 0x00FF);
	PCA0CPH0 = (num & 0xFF00)>>8;

	EA = 0;
	EIE1 &= ~0x10;       
}

/**
 * @brief este delay esta hecho exclusivamente para el pwm y no puede usarse en otro lado porque puede interferir
 * con el funcionamiento del mismo
 * 
 * @details [long description]
 * 
 * @param tiempo [description]
 */
void delay(int tiempo)
{

	int i = 0;

	EIE1 |= 0x10;                       // Enable PCA interrupts
	EA = 1;

	while(1)
	if(CCF0)
	{
		CCF0 = 0;
		i++;
		if(i >= tiempo) break;
	}

	EA = 0;
	EIE1 &= ~0x10;     
	// IE = aux1;
	// EIE1 = aux2; // reestablecemos los valores del registro de interrupcion.

}

// char getchar_pasivo()
// {
// 	unsigned char res;

// 	ES0 = 1; // habilitar interrupcion de UART
// 	if (f_UART)
// 	{
// 		EA = 0; // inhabilitar interrupciones globales
// 		f_UART = false;
// 		printf("STOP\n");
// 		break;
// 	}
// 	ES0 = 0;

// 	res = (unsigned char)SBUF0; // obtengo el caracter leido accediendo al registro asociado a la UART

// 	return res;
// }