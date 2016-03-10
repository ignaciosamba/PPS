/**
 * @file conversor.c
 * @author Sambataro, Ignacio; Mantovani, Luciano
 * @date 2015
 * @brief este archivo define el comportamiento de todas las funciones que intervienen en la logica a nivel de
 * registro y a nivel operativo del conversor analogico digital.
 */

#include "headers.h"
#include "conversor.h"

short int dato_n;
unsigned short int num;
unsigned long dato_conversor;

/**
 * @brief Esta funcion obtiene un valor de los registros ADC0H, ADC0M, y ADC0L. Que corresponden al valor de la
 * conversion actual.
 * @details El valor de conversion tiene un total de 24 bits, y esta repartido en 3 registros de 8 bits.
 * Para obtener este valor es necesario hacer un calculo teniendo en cuenta la tension de referencia con la que
 * se trabaja.
 * @return Devuelve el valor obtenido en los registros
 */
unsigned long convertir(void)
{
	static LONGDATA rawValue;
	unsigned long mV;
	
   // Copiar el valor del registro de conversion del adc en una variable local
	rawValue.Byte[Byte3] = 0x00;
	rawValue.Byte[Byte2] = (unsigned char)ADC0H; // para ADC de 24 bits
	rawValue.Byte[Byte1] = (unsigned char)ADC0M; // para ADC de 24 bits
	rawValue.Byte[Byte0] = (unsigned char)ADC0L; // para ADC de 24 bits

	// rawValue.Byte[Byte1] = (unsigned char)ADC0H; // para ADC de 16 bits
	// rawValue.Byte[Byte0] = (unsigned char)ADC0M; // para ADC de 16 bits
	//                           Vref (mV)
	//   medicion (mV) =   --------------- * result (bits)
	//                       (2^24)-1 (bits)
	//
	//   medicion (mV) =  result (bits) / ((2^resolucion)-1 (bits) / Vref (mV))
	//
	//
	//   Con un voltaje de referencia de 2.5 V:
	//
	//   medicion (mV) =  result (bits) / ((2^resolucion)-1 / 2500)
	//
	//   medicion (mV) =  result (bits) / ((2^resolucion)-1 / 2500)
	//
	//   medicion (mV) =  result (bits) / (16777215 / 2500)   para 24 bits
	//   medicion (mV) =  result (bits) / (65535 / 2500)   para 16 bits
	//
	//   medicion (mV) =  result (bits) / (6710)  para 24 bits
	//   medicion (mV) =  result (bits) / (26)   para 16 bits

	// se calcula el voltaje medido segun el voltaje de referencia

	mV = rawValue.result / 6710; // para adc de 24 bits
	// mV = rawValue.result / 26; // para adc de 16 bits        

	return mV;

}

/**
 * @brief Configura la ganancia a la entrada del ADC.
 * @details La ganancia determina la magnitud de la señal a medir. El valor de amplificacion puede ser de 
 * un factor de 2 a 128
 * 
 * @param shellstr se pasa la direccion de la estructura entera como parametro. El valor de args[0] determina
 * el factor por el que se potencia a 2 para obtener la ganancia.
 * @return devuelve la misma estructura
 */
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
 * @brief Cambia el pin actual medido al siguiente.
 * @details Cada vez que se llama esta funcion, se analiza el estado actual del registro ADC0MUX, y segun su 
 * valor, se calcula el valor siguiente. Esta hecha de forma que recorra todos los pines en todos sus modos
 * posibles en forma de escalera; de forma que si se llama en un ciclo infinito, recorreria todos los pines
 * en todas sus configuraciones, con una frecuencia igual para cada pin.
 */
void cambiar_pin()
{
	ADC0MD = 0x80; // ADC en modo idle
	if((ADC0MUX & 0x0F) == 0x08) // si los 4 LSB de ADC0MUX son 8, estamos en modo single ended
	{
		if(ADC0MUX == 0x78) // si estamos en el ultimo pin del modo single ended, hay que pasar a modo diferencial
		{
			ADC0CN |= 0x10; // se habilita el modo diferencial
			// ADC0DAC |= 0xBF;
			ADC0MUX = 0x01; // se setean los pines 0 y 1 en modo diferencial
			ADC0MD = 0x83; // ADC en modo conversion continua
			return;
		}
		ADC0MUX = ADC0MUX + 0x10; // se cambia al pin siguiente
		ADC0MD = 0x83; // ADC en modo conversion continua
		return;
	}
	else if((ADC0MUX & 0x0F) < 0x08)// si los 4 LSB de ADC0MUX son menores a 8, estamos en modo diferencial
	{
		if(ADC0MUX == 0x67) // si estamos en el ultimo par de pines del modo diferencial, hay que pasar a modo single-ended.
		{
			ADC0CN &= ~0x10; // se habilita el modo bipolar
			ADC0MUX = 0x08; // se setea el pin 0 en modo single-ended
			ADC0MD = 0x83; // ADC en modo conversion continua
			return;
		}		
		ADC0MUX = ADC0MUX + 0x22; // se cambia al siguiente par de pines
		ADC0MD = 0x83; // ADC en modo conversion continua
		return;
	}
}

/**
 * @brief Envia datos por la interfaz serial
 * @details el formato de envio es: MODO,PIN,VALOR. Donde el modo puede ser SE o DF, siendo single-ended o 
 * diferencial, respectivamente; el pin es el pin donde se midio, en el caso que sea diferencial, se le debe 
 * sumar 1 al pin mostrado para tener los pines donde se midio; y el valor es el valor medido.
 * 
 * @param long El dato a enviar
 */
void enviar_dato(unsigned long int *dato)
{
	char num_pin;
	num_pin = (char)ADC0MUX;

	if((num_pin & 0x0F) == 0x08)
	{
		// printf("SE,%c,%lu,z", (num_pin >> 4) + '0',*dato);
		printf("%05lu\n",*dato);
	}
	else if((num_pin & 0x0F) < 0x08)
	{
		if(*dato < 1250)
			// printf("DF,%c,+%lu\n", (num_pin >> 4) + '0',(*dato)*2);
			printf("+%04lu\n",(*dato)*2);
		else
			// printf("DF,%c,-%lu\n", (num_pin >> 4) + '0',(2520 - *dato)*2);
			printf("-%04lu\n",(2520 - *dato)*2);
		/**
		 * hay toda una explicacion que duro bastante tiempo de porque pasa
		 */
	}
}

/**
 * @brief Analiza el buffer de pines para determinar si el envio esta o no habilitado
 * @details Esta funcion se encarga de verificar si el pin medido esta habilitado para el envio o no.
 * Esta funcion fue hecha para trabajar en conjunto con la funcion cambiar_pin(). La idea es que se haga un
 * barrido constante de todos los pines en todos sus modos, pero que se envien solo los que deban enviarse.
 * La informacion de si se envia o no esta en los buffers "buffer_adc_count" y "buffer_adc". El primero contiene
 * los valores iniciales de cada pin en cada modo, y el segundo contiene los valores actuales. Cada vez que se 
 * hace un llamado a esta funcion, el los valores de buffer_adc se decrementan en 1. Cuando un elemento del array
 * llega a 1, esta habilitado para el envio. Si un elemento tiene valor 0, el pin correspondiente esta deshabilitado.
 * @return devuelve true si el pin actual esta habilitado para enviar, 0 si no esta habilitado.
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
			return 0; // canal deshabilitado
		}
		if(shell->buffer_adc [idx] == 1)
		{
			shell->buffer_adc [idx] = shell->buffer_adc_count[idx]; // canal habilitado listo para imprimir. se resetea al valor inicial
			return 1;
		}
		if(shell->buffer_adc [idx] > 1)
		{
			shell->buffer_adc[idx]--; // canal habilitado aun no listo para imprimir. se decrementa
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


/**
 * @brief carga uno de los pines del ADC en modo single-ended con un valor de 0 a 65536
 * @details el arreglo buffer_adc_count contiene los valores de todos los pines en todas las configuraciones
 * posibles. Esta funcion se encarga de cargar los valores desde el 0 al 7 de buffer_adc_count que corresponden a las configuraciones
 * de los pines en modo single-ended.
 * El valor con el que se cargen sera despues lo que determina la frecuencia de salida de los datos por el medio
 * de transmision. Mientras mas grande sea el valor, menor es la frecuencia. Si se carga con el valor 0, el pin
 * ingresado se deshabilita
 * 
 * @param shellstr se pasa la direccion de la estructura entera como parametro.
 * El campo args[0] da el valor del indice de buffer_adc_count. el resto de los argumentos de args dan el valor
 * con el que se cargara el elemento del array.
 * 
 * @warning esta funcion no tiene ningun efecto si el valor shell->args[0] es menor que 0 o mayor que 7
 */
void cargar_buffer_single(struct shellstr *shell)
{
	num = (unsigned)(atoi(shell->args + 2));
	if(num > 65536)
	{
		shell->errn = 406;
		return;
	}

	dato_n = shell->args[0] - '0';
	if(dato_n >= 0 && dato_n < 8)
	shell->buffer_adc_count[dato_n] = num;

	shell->errn = 251;
}


/**
 * @brief carga uno de los pines del ADC en modo diferencial con un valor de 0 a 65536
 * @details el arreglo buffer_adc_count contiene los valores de todos los pines en todas las configuraciones
 * posibles. Esta funcion se encarga de cargar los valores desde el 8 al 11 de buffer_adc_count que corresponden a las configuraciones
 * de los pines en modo diferencial.
 * El valor con el que se cargen sera despues lo que determina la frecuencia de salida de los datos por el medio
 * de transmision. Mientras mas grande sea el valor, menor es la frecuencia. Si se carga con el valor 0, el pin
 * ingresado se deshabilita
 * 
 * @param shellstr se pasa la direccion de la estructura entera como parametro.
 * El campo args[0] da el valor del indice de buffer_adc_count. Este valor corresponde a uno de los dos pines que seran
 * parte de la medicion por estar trabajando en modo diferencial. Solo se permite ingresar los pines 0,2,4 y 6; que 
 * corresponden a la medicion de los pines 0-1; 2-3; 4-5; y 5-6 respectivamente.
 * con el que se cargara el elemento del array.
 * 
 * @warning esta funcion no tiene ningun efecto si el valor shell->args[0] es impar, menor que 0 o mayor que 6
 */
void cargar_buffer_dif (struct shellstr *shell)
{
	num = (unsigned)(atoi(shell->args + 2));

	switch(shell->args[0])
	{
		case '0': dato_n = 8; break;
		case '2': dato_n = 9; break;
		case '4': dato_n = 10; break;
		case '6': dato_n = 11; break;
		default: shell->errn = 406; return; 
	}

	shell->buffer_adc_count[dato_n] = num;

	shell->errn = 252;
}

/**
 * @brief devuelve el valor de una medicion en el momento que se ingresa la instruccion
 * @details 
 * 
 * @param shellstr [description]
 */
void get_single_ended(struct shellstr *shell)
{
	ADC0MUX = (shell->args[0] << 4) + 8;

	AD0INT = 0;		// se inicializa en 0 el bit de conversion completa del ADC.	
	ADC0CF = 0x00;  // se usa el FAST FILTER.
	ADC0MD = 0x82;	// Habilitar conversion en modo continuo.

	EIE1 |= 0x08;    // Enable ADC0 Interrupts
	EA = 1;          // habilitar interrupciones globales


	while (!f_dato_convertido);
	f_dato_convertido = false;

	dato_conversor = convertir();
	enviar_dato(&dato_conversor);

    ADC0MD = 0x00;
	EA = 0;

	EIE1 &= ~0x08;    // Disable ADC0 Interrupts
	shell->errn = 0;

}

void get_differential(struct shellstr *shell)
{
	switch(shell->args[0])
	{
		case '0': ADC0CN |= 0x10; ADC0MUX = 0x01; break;
		case '2': ADC0CN |= 0x10; ADC0MUX = 0x23; break;
		case '4': ADC0CN |= 0x10; ADC0MUX = 0x45; break;
		case '6': ADC0CN |= 0x10; ADC0MUX = 0x67; break;
		default: shell->errn = 406; return; 
	}
	
	AD0INT = 0;		 // se inicializa en 0 el bit de conversion completa del ADC	
	ADC0CN |= 0x00;  // se habilita el modo diferencial
	ADC0MD = 0x82;	 // Habilitar conversion en modo continuo
	EIE1 |= 0x08;    // Enable ADC0 Interrupts
	EA = 1;          // habilitar interrupciones globales

	while (!f_dato_convertido);
	f_dato_convertido = false;
	dato_conversor = convertir();	
	enviar_dato(&dato_conversor);

    ADC0MD = 0x00;
	EA = 0;
	
	EIE1 &= ~0x08;    // Disable ADC0 Interrupts
	shell->errn = 0;
}


void mostrar_config_actual(struct shellstr * shell)
{
    char i;
       for (i= 0 ; i<TAM_SINGLE ; i++)
    {
        printf("ADC[%i]: %u\n", (int)i, shell->buffer_adc_count[i]/* - '0'*/);
    }

    printf("ADC0CN: 0x%c\n", (char)ADC0CN + '0');
}