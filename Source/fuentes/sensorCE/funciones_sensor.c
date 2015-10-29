#include "../headers.h"
#include "funciones_sensor.h"


#define V_FASE_1 42200
#define V_FASE_2 42100
#define V_ARRANQUE 33264
#define V_ESTABLE 36000
#define VELOCIDAD_APAGADO 65500
#define VUELTAS_CADA_100MS 18 //para una velocidad ideal de 3600 rpm. valor explicado en la funcion contar_RPM
#define HISTERESIS 2
#define CORRECCION 50


unsigned short int velocidad = V_ESTABLE;
unsigned long eventos;
sbit HABILITAR_MOTOR = P0^2;
sbit LED = P0^6;                          // LED='1' means ON

void RPM_instantaneo()
{

	// 4 eventos del timer0 son 1 vuelta del motor al tener este 4 aspas
	// cantidad de vueltas en 500 ms * 2 = vueltas por segundo.
	// (vueltas / 4) * 120 = rps
	// vueltas * 30 = rps

	// la misma logica con 100 ms
	// cantidad de vueltas en 100 ms = vueltas por segundo.
	// (eventos / 4) * 10 = rpm
	// eventos * 150 = rpm
	printf("%lu +-150 rps\n", eventos*150);
}

void contar_RPM(void) // utiliza timer0 y timer3. llamada por interrupcion de timer3
{
	static LONGDATA rawValue;
	unsigned long res = 0;

	rawValue.Byte[Byte3] = 0x00;
	rawValue.Byte[Byte2] = 0x00;
	rawValue.Byte[Byte1] = (unsigned char)TH0;
	rawValue.Byte[Byte0] =(unsigned char)TL0;

	res = rawValue.result;

	eventos = res;

	//res tiene la cantidad de vueltas en 100 ms teniendo en cuenta que esta funcion se llama cada 3 interrupciones
	//del timer3 que son aprox 100ms.

	//teniendo en cuenta esto, tenemos un rpm ideal que es mas o menos 3600 rpm.. para que sea asi, en un minuto
	//entero el contador de eventos tiene que haber contado 4 * 3600 veces = 14.400 veces.
	//y en un segundo 4 * (3600/60) = 240 veces
	//y en 100 milisegundos 4 * (3600/600) = 18 veces
	//con este ultimo valor se fijo la constante VUELTAS_CADA_100MS

	//como esta funcion se llama cada 100 milisegundos, se controla acorde colocando una velocidad estable


	control_RPM(eventos,(unsigned)VUELTAS_CADA_100MS);
  	
	TH0 = 0;           // Resetear valor de timer0
	TL0 = 0;    

}
/**
 * @brief agrega una histeresis al funcionamiento del motor que evita el desvio de las RPM
 * @details [long description]
 */
void control_RPM(unsigned short eventos_real, unsigned short eventos_ideal)
{
	// static short int correcciones_mas;
	// static short int correcciones_menos;
	if(eventos_real > eventos_ideal + HISTERESIS) // si las eventos son muy altas
	{
		velocidad +=CORRECCION; //parece que se baja pero restarla es subirla
		set_Pwm(velocidad); // se baja la velocidad relativa
		// printf("se controlo para que vaya mas despacio\neventos_ideal = %d\neventos_real = %d", eventos_ideal, eventos_real);
		// correcciones_menos++;
	}

	if(eventos_real < eventos_ideal - HISTERESIS) // si las eventos son muy bajas
	{
		velocidad -=CORRECCION; //parece que se baja pero restarla es subirla
		set_Pwm(velocidad); // se sube la velocidad relativa
		// correcciones_mas++;
		// printf("se controlo para que vaya mas rapido\n");
	}

	// if(correcciones_mas + correcciones_menos >= 10)
	// {
		// printf("se corrigio 10 veces..\n%d de mas\n%d de menos\n", correcciones_mas, correcciones_menos);
	// 	correcciones_menos = 0;
	// 	correcciones_mas = 0;
	// }

	if(velocidad < V_ARRANQUE)
		apagar_motor();			//si llega a ir demasiado rapido, se apaga por seguridad.
}

/**
 * @brief arranca el motor usando el pwm de la placa
 * @details [long description]
 */
void arrancar_motor(void) 
{

	// EIE1 |= 0x10;                       // Enable PCA interrupts
	// EA = 1;
	HABILITAR_MOTOR = 1;
	delay(1000);
	
	printf("\nFase 1...\n");
	set_Pwm(V_FASE_1);
	delay(600);
	printf("Fase 2...\n");
	set_Pwm(V_FASE_2);
	delay(600);

	// printf("Fase 3...\n");
	// set_Pwm(V_FASE_3);
	// delay(600);
	printf("Arranque...\n");
	set_Pwm(V_ARRANQUE);
	delay(600);
	printf("Nivel estable\n");
	set_Pwm(V_ESTABLE);

    EIE1 |= 0x80; //habilitar interrupcion de timer3
	EA = 1; // habilitar interrupciones globales para hacer que interrumpa timer3 para realizar el control

	// EA = 0;
	// EIE1 &= ~0x10;      
}

void apagar_motor(void) 
{
	//printf("01011\n");
    EIE1 &= ~0x80; //deshabilitar interrupcion de timer3
	set_Pwm(VELOCIDAD_APAGADO);
	HABILITAR_MOTOR = 0;
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
	if(CCF0) // bandera de interrupciones del contador del PCA. Se cuentan interrupciones para generar el delay
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


void resetear_motor(void) 
{
	long unsigned int k = 0;

	// EIE1 |= 0x10;                       // Enable PCA interrupts
	// EA = 1;
	HABILITAR_MOTOR = 1;
	delay(1000);
	printf("reestableciando valores del motor\n");
	//printf("\nFase 1...\n");
	// for(i = 0; i < 20000; i = i + 100)
	while(k < 30000)
	{
		printf("%lu\n", 53000 - k);
		
		LED = 1;
		set_Pwm(53000 - k);
		delay(80);
		LED = 0;
		delay(80);

		k = k + 500;
	}

    EIE1 |= 0x80; //habilitar interrupcion de timer3
	EA = 1; // habilitar interrupciones globales para hacer que interrumpa timer3 para realizar el control

	// EA = 0;
	// EIE1 &= ~0x10;      
}

void configurar_motor(void)
{
	unsigned long int opcion = 0;
	printf("configuracion del motor.. cualquier tecla hace toggle en la aceleracion de 0 a 100. 's' sale\n");
	HABILITAR_MOTOR = 1;
	// delay(1000);

	while(getchar() != 's')
	{
		set_Pwm(opcion);

		if(opcion == 0)
		{	
			printf("PWM = '1'\n");
			opcion = 65536;
		}
		else 
		{
			printf("PWM = '0'\n");
			opcion = 0;
		}
	}

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