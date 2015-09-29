#include "../headers.h"
#include "funciones_sensor.h"

#define V_FASE_1 42200
#define V_FASE_2 42100
#define V_ARRANQUE 33264
#define V_ESTABLE 36000
#define VELOCIDAD_APAGADO 65500
#define VELOCIDAD_ESTABLE_RPS 3700


unsigned short int velocidad = V_ESTABLE;
unsigned long rps;

void RPS_instantaneo()
{
	printf("%lu +-30 rps\n", rps);
}

void contar_RPS(void) // utiliza timer0 y timer3. llamada por interrupcion de timer3
{
	static LONGDATA rawValue;
	unsigned long res = 0;

	rawValue.Byte[Byte3] = 0x00;
	rawValue.Byte[Byte2] = 0x00;
	rawValue.Byte[Byte1] = (unsigned char)TH0;
	rawValue.Byte[Byte0] =(unsigned char)TL0;

	res = rawValue.result;

	// rps = res * 30; 
	rps = res * 10; 

	// 4 eventos del timer0 son 1 vuelta del motor al tener este 4 aspas
	// cantidad de vueltas en 500 ms * 2 = vueltas por segundo.
	// (vueltas / 4) * 120 = rps
	// vueltas * 30 = rps

	// la misma logica con 100 ms
	// cantidad de vueltas en 100 ms = vueltas por segundo.
	// (cuenta / 4) * 10 = rps
	// cuenta * 150 = rps

	// esto da una precision de 30 rps. osea que cada resultado es +-30

	control_RPS(rps,(unsigned)VELOCIDAD_ESTABLE_RPS);
  	
	TH0 = 0;           // Resetear valor de timer0
	TL0 = 0;    

}
/**
 * @brief agrega una histeresis al funcionamiento del motor que evita el desvio de las RPS
 * @details [long description]
 */
void control_RPS(unsigned short rps_real, unsigned short rps_ideal)
{
	// static short int correcciones_mas;
	// static short int correcciones_menos;
	if(rps_real > rps_ideal + 200) // si las rps son muy altas
	{
		velocidad +=50;
		set_Pwm(velocidad); // se sube la velocidad relativa
		// printf("se controlo para que vaya mas despacio\nrps_ideal = %d\nrps_real = %d", rps_ideal, rps_real);
		// correcciones_menos++;
	}

	if(rps_real < rps_ideal - 200) // si las rps son muy bajas
	{
		velocidad -=50;
		set_Pwm(velocidad); // se baja la velocidad relativa
		// correcciones_mas++;
		// printf("se controlo para que vaya mas rapido\n");
	}

	// if(correcciones_mas + correcciones_menos >= 10)
	// {
	// 	printf("se corrigio 10 veces..\n%d de mas\n%d de menos\n", correcciones_mas, correcciones_menos);
	// 	correcciones_menos = 0;
	// 	correcciones_mas = 0;
	// }
}

/**
 * @brief arranca el motor usando el pwm de la placa
 * @details [long description]
 */
void arrancar_motor(void) 
{

	// EIE1 |= 0x10;                       // Enable PCA interrupts
	// EA = 1;
	
	//printf("\nFase 1...\n");
	set_Pwm(V_FASE_1);
	delay(600);
	//printf("Fase 2...\n");
	set_Pwm(V_FASE_2);
	delay(600);
	//printf("Arranque...\n");
	set_Pwm(V_ARRANQUE);
	delay(600);
	//printf("Nivel estable\n");
	set_Pwm(V_ESTABLE);

	EA = 1; // habilitar interrupciones globales para hacer que interrumpa timer3 para realizar el control

	// EA = 0;
	// EIE1 &= ~0x10;      
}

void apagar_motor(void) 
{
	//printf("01011\n");
	set_Pwm(VELOCIDAD_APAGADO);
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
	// EIE1 |= 0x10;                       // Enable PCA interrupts
	// EA = 1;

	// while(CCF0 != 0);       // espera que termine el ciclo de trabajo

	// luego setea los valores
	PCA0CPL0 = (num & 0x00FF);
	PCA0CPH0 = (num & 0xFF00)>>8;

	// EA = 0;
	// EIE1 &= ~0x10;       
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

	// EIE1 |= 0x10;                       // Enable PCA interrupts
	// EA = 1;

	while(1)
	if(CCF0)
	{
		CCF0 = 0;
		i++;
		if(i >= tiempo) break;
	}

	// EA = 0;
	// EIE1 &= ~0x10;     
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