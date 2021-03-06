#include "../headers.h"
#include "funciones_sensor.h"


// #define V_FASE_1 42200
// #define V_FASE_1 48200 // 700uS
#define V_FASE_1 39500 // 1150uS TIEMPO EN ALTO
// #define V_FASE_2 42100
// #define V_FASE_2 46300 // 900uS
#define V_FASE_2 37200 // 1200uS
// #define V_MAXIMA 33264
#define V_MAXIMA 34864
// #define V_ESTABLE 44000 // 1100uS 
// #define V_ESTABLE 46300
// #define V_ESTABLE 33400 // 1350uS 
#define V_ESTABLE 45600 
#define VELOCIDAD_APAGADO 48200  // 700uS
#define VUELTAS_CADA_100MS 30 //para una velocidad ideal de 3600 rpm. valor explicado en la funcion contar_RPM
#define VUELTAS_CADA_200MS 33 //para una velocidad ideal de 3600 rpm. valor explicado en la funcion contar_RPM
#define HISTERESIS 5
#define CORRECCION 10
#define WATCHDOG_INITIAL 100
#define ONDA_CUADRADA 32768


unsigned short int velocidad = V_ESTABLE;
unsigned long eventos;
// unsigned long hertz;
// unsigned long print_hertz;
// unsigned int hertz_count;
sbit HABILITAR_MOTOR = P0^2;
sbit LED = P0^6;                          // LED='1' means ON
short int watchdog_value = WATCHDOG_INITIAL;

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
	printf("%lu\n", eventos);
}

void RPM_continuo()
{
	int i;
	while(1)
	{
		for(i = 0; i < 9000; i++);
		printf("%lu\n", eventos);
	}
}
void enable_int()
{
    EIE1 |= 0x80; //habilitar interrupcion de timer3
	EA = 1; // habilitar interrupciones globales para hacer que interrumpa timer3 para realizar el control
}

void disable_int()
{
    EIE1 &= ~0x80; //deshabilitar interrupcion de timer3
}

// void get_hertz()
// {
// 	printf("%lu\n", print_hertz);
// }

void contar_RPM(void) // utiliza timer0 y timer3. llamada por interrupcion de timer3
{
	static LONGDATA rawValue;
	unsigned long res = 0;

	// if (hertz_count >= 5)
	// 	hertz_count = 0;


	rawValue.Byte[Byte3] = 0x00;
	rawValue.Byte[Byte2] = 0x00;
	rawValue.Byte[Byte1] = (unsigned char)TH0;
	rawValue.Byte[Byte0] =(unsigned char)TL0;

	res = rawValue.result;

	eventos = res;

	// if (hertz_count == 0)
	// {
	// 	print_hertz = hertz;
	// 	hertz = 0;
	// }

	// hertz = hertz + res;
	// hertz_count++;

	//res tiene la cantidad de vueltas en 100 ms teniendo en cuenta que esta funcion se llama cada 3 interrupciones
	//del timer3 que son aprox 100ms.

	//teniendo en cuenta esto, tenemos un rpm ideal que es mas o menos 3600 rpm.. para que sea asi, en un minuto
	//entero el contador de eventos tiene que haber contado 4 * 3600 veces = 14.400 veces.
	//y en un segundo 4 * (3600/60) = 240 veces
	//y en 100 milisegundos 4 * (3600/600) = 18 veces
	//con este ultimo valor se fijo la constante VUELTAS_CADA_100MS

	//como esta funcion se llama cada 100 milisegundos, se controla acorde colocando una velocidad estable


	control_RPM(eventos,(unsigned)VUELTAS_CADA_200MS);
  	
	TH0 = 0;           // Resetear valor de timer0
	TL0 = 0;    

	watchdog_value--;
	// check_watchdog();

	return;

}

/**
 * @brief Checkea el valor de watchdog_value para verificar que el motor no este en velocidades muy altas que puedan provocar que el sistema este en peligro.
 * @details La variable watchdog_value se resetea cada vez que se controla la velocidad del motor. En caso que el programa no pueda controlar la velocidad del motor por la razon que sea, es necesario un watchdog que corte el funcionamiento del motor por inanicion de control. Eso es justamente lo que logra esta funcion.
 * 
 */
// void check_watchdog()
// {
// 	if(watchdog_value == 0)
// 	{
// 		// apagar_motor();
// 	}
// }

/**
 * @brief Refresca el valor de watchdog_value
 * @details Esta funcion impide que el motor se apague por inanicion de control de velocidad.
 */
void refresh_watchDog()
{
	watchdog_value = WATCHDOG_INITIAL;
}

/**
 * @brief Controla la velocidad del motor para que este siempre con valores cercanos a una velocidad ideal pre-programada
 * @details Con una histeresis, controla si la velocidad del motor es mayor o menor a la ideal. En caso de ser menor, la aumenta, y en caso de ser mayor, la disminuye. Es un control por software que puede no ser muy preciso pero es suficiente para los fines del motor. Contiene ademas un control que verifica que la velocidad del motor no sobrepase la maxima. En caso que esto ocurra, se apaga el motor por razones de seguridad.
 */
void control_RPM(unsigned short eventos_real, unsigned short eventos_ideal)
{
	if(eventos_real > eventos_ideal + HISTERESIS) // si las eventos son muy altas
	{
		velocidad +=CORRECCION; //parece que se sube pero sumarla es bajarla
		set_Pwm(velocidad); // se baja la velocidad relativa
	}

	if(eventos_real < eventos_ideal - HISTERESIS) // si las eventos son muy bajas
	{
		velocidad -=CORRECCION; //parece que se baja pero restarla es subirla
		set_Pwm(velocidad); // se sube la velocidad relativa
	}

	// if(velocidad < V_MAXIMA)
		// apagar_motor();			//si llega a ir demasiado rapido, se apaga por seguridad.
}

/**
 * @brief arranca el motor usando el pwm de la placa
 * @details [long description]
 */
void arrancar_motor(void) 
{
	// HABILITAR_MOTOR = 1;
	// set_Pwm(V_FASE_1);S
	// delay(1500);
	// set_Pwm(V_FASE_2);
	// delay(1500);
	// set_Pwm(V_ESTABLE);

	unsigned long int comienzo = 48200;
	unsigned long int velocidad = 48200;
	unsigned long int vel_init = 45600;
	int i = 0;


	set_Pwm(comienzo);
	// delay(1000);
	HABILITAR_MOTOR = 1;
	delay(2000);


	// while(velocidad > vel_init)
	for (velocidad = 48200; velocidad > vel_init; velocidad = velocidad - 10)
	{	
		// RPM_instantaneo();
		// printf("%lu\n", eventos);
		set_Pwm(velocidad);
		// velocidad = velocidad - 10;
		// delay(50);
	}

	// set_Pwm(V_FASE_1);
	// delay(800);
	// set_Pwm(V_FASE_2);
	// delay(800);


    EIE1 |= 0x80; //habilitar interrupcion de timer3
	EA = 1; // habilitar interrupciones globales para hacer que interrumpa timer3 para realizar el control

	// RPM_continuo();
}

/**
 * @brief arranca el motor usando el pwm del microcontrolador, sin control de velocidad
 * @details [long description]
 */
void arrancar_motor_sin_control(void) 
{
		// threshold = 46300 
	unsigned long int comienzo = 48200;
	unsigned long int velocidad = 48200;
	unsigned long int vel_init = 45600;
	int i = 0;


	set_Pwm(comienzo);
	// delay(1000);
	HABILITAR_MOTOR = 1;
	delay(2000);


	while(velocidad > vel_init)
	{	
		// RPM_instantaneo();
		// printf("%lu\n", velocidad);
		set_Pwm(velocidad);
		velocidad = velocidad - 100;
		delay(50);
	}

	// set_Pwm(V_FASE_1);
	// delay(800);
	// set_Pwm(V_FASE_2);
	// delay(800);
////////////////////////////
	// delay(600);
	// delay(600);
	// set_Pwm(33264);
	// delay(600);
	// set_Pwm(36000);
	// delay(600);
	// set_Pwm(32000);
	// delay(600);

	// set_Pwm(40000);
	// RPM_continuo();
}

void generar_onda_cuadrada(void)
{
   // PCA0MD = 0x00; // Use SYSCLK as time base
   // PCA0CPM0 |= 0x46; // ECOM, TOG, & PWM en 1
   // PCA0CPM0 &= ~0x80; // PWM16 en 0
   // PCA0CPH0 = 0x00;

	set_Pwm(ONDA_CUADRADA);
}

void apagar_motor(void) 
{
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
 */
void set_Pwm(unsigned int num)
{
	PCA0CPL0 = (num & 0x00FF);
	PCA0CPH0 = (num & 0xFF00)>>8;
}

/**
 * @brief Delay para el contador del PCA
 * @details Funcion que genera un delay necesario para los intervalos necesarios para generar los codigos para el driver PWM del motor brushless
 * @param tiempo tiempo de delay medido en cantidad de interrupciones (no hay referencia relativa a segundos)
 * @warning este delay esta hecho exclusivamente para el pwm y no puede usarse en otro lado porque puede interferir con el funcionamiento del mismo
 */
void delay(int tiempo)
{
	int i = 0;

	while(1)
	if(CCF0) // bandera de interrupciones del contador del PCA. Se cuentan interrupciones para generar el delay
	{
		CCF0 = 0;
		i++;
		if(i >= tiempo) break;
	}
}

/**
 * @brief Genera los codigos en señales PWM necesarios para reestablecer los valores del driver que hacen que el sensor funcione correctamente con respecto a nuestro sistema.
 */
void resetear_motor(void) 
{
	long unsigned int k = 0;
	HABILITAR_MOTOR = 1;
	delay(1000);
	printf("reestableciando valores del motor\n");
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
}

/**
 * @brief Coloca el driver del motor en modo configuracion
 * @details En este modo, el PCA genera dos distintas señales de PWM de forma que cualquier tecla que se presione hace un toggle entre estas dos señales, eligiendo asi las distintas opciones de configuracion. Presionando la tecla "s" se sale del modo de configuracion 
 */
void configurar_motor(void)
{
	unsigned long int opcion = 48200; // original en 48200
	unsigned long int cosa = 0;
	set_Pwm(opcion);
	HABILITAR_MOTOR = 1;

	while(opcion - cosa > 30000)
	{	
		getchar();
		set_Pwm(opcion - cosa);
		cosa = cosa + 100;
		printf("%lu\n", (opcion - cosa));
	}



	delay(2500);

	HABILITAR_MOTOR = 0;
}

