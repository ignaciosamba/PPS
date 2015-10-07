/** Este archivo actua con la memoria flash y guarda las opciones configuracion
 * cada vez que hubo una configuracionnueva. Tambien saca las configuraciones de la
 * memoria y las carga en el programa en cada inicio del dispositivo.
 *  Tambien configura los registros de las interrupciones
**/
#include "headers.h"
#include "configurador.h"

sbit LED = P0^7;
char int_aux1;
char int_aux2;

void iniciar_puertos (void)
{
   XBR1     |= 0x40;                    // Habilitar el crossbar
   P0MDOUT |= 0x10;                    // Habilitar UTX como push-pull output
   P1MDOUT |= 0x02;                              // Habilitar led P1.1 como push pull
   // P0MDIN |= 0x0C;                  // P0.3 y P0.4 tienen que ser entrada digital
   
   P0MDOUT |= 0x04;                  // habilitar P0.2 como push pull para el rele mecanico
   P0 &= ~0x04;               //inicializa en 0 
}

void iniciar_sysclock (void)
{
   OSCICN |= 0x03;                     // configuracion del oscilador para la maxima frecuencia
   RSTSRC  = 0x04;                     // Enable missing clock detector
   CLKSEL = 0x00;                      // selecciona el clock interno como fuente para SYSCLK

}


int iniciar_ADC(void)
{
	REF0CN |= 0x03;                     // Enable internal Vref
	ADC0CN = 0x00;                      // Gain = 1, Unipolar mode
	ADC0CF = 0x00;                      // Interrupts upon SINC3 filter output
	                                   // and uses internal VREF

	ADC0CLK = (SYSCLK/MDCLK)-1;         // Generate MDCLK for modulator.
	                                   // Ideally MDCLK = 2.4576MHz

	// Program decimation rate for desired OWR
	ADC0DEC = ((unsigned long) MDCLK / (unsigned long) OWR /
	          (unsigned long) 128) - 1;

	ADC0BUF = 0x00;                     // Turn off Input Buffers
	ADC0MUX = 0x08;                     // Select AIN0.2

	ADC0MD = 0x81;                      // Start internal calibration
	while(AD0CALC != 1);                // Wait until calibration is complete

	ADC0MD  = 0x80;                     // Enable the ADC0 (IDLE Mode)
	
	return 0;
}



void iniciar_UART(void)
{

//-----------------------------------------------------------------------------
// UART0_Init
//-----------------------------------------------------------------------------
//
// Configure the UART0 using Timer1, for <BAUDRATE> and 8-N-1.
//
   
   XBR0     |= 0x01;                    // Enable UART to Pins P0.4, P0.5
   XBR1     |= 0x40;                    // Enable Crossbar 

   P0SKIP   = 0x00;                    // Skip No Port Pins
   P0MDOUT |= 0x10;                    // Enable UTX as push-pull output
   P0MDIN  |= 0x20;					   // Enable URX pin as digital input.
   
   
   
   SCON0 = 0x10;                       // SCON0: 8-bit variable bit rate
                                       //        level of STOP bit is ignored
                                       //        RX enabled
                                       //        ninth bits are zeros
                                       //        clear RI0 and TI0 bits
   if (SYSCLK/BAUDRATE/2/256 < 1) {
      TH1 = -(SYSCLK/BAUDRATE/2);
      CKCON |=  0x08;                  // T1M = 1; SCA1:0 = xx
   } else if (SYSCLK/BAUDRATE/2/256 < 4) {
      TH1 = -(SYSCLK/BAUDRATE/2/4);
      CKCON &= ~0x0B;                  // T1M = 0; SCA1:0 = 01                  
      CKCON |=  0x01;
   } else if (SYSCLK/BAUDRATE/2/256 < 12) {
      TH1 = -(SYSCLK/BAUDRATE/2/12);
      CKCON &= ~0x0B;                  // T1M = 0; SCA1:0 = 00
   } else {
      TH1 = -(SYSCLK/BAUDRATE/2/48);
      CKCON &= ~0x0B;                  // T1M = 0; SCA1:0 = 10
      CKCON |=  0x02;
   }

   TL1 = TH1;                          // init Timer1
   TMOD &= ~0xf0;                      // TMOD: timer 1 in 8-bit autoreload
   TMOD |=  0x20;                       
   TR1 = 1;                            // START Timer1
   TI0 = 1;                            // Indicate TX0 ready


}


void iniciar_timer0(void)
{
   XBR1 |= 0x10; // habilitar timer0 en el crossbar
   TH0 = 0;           // Init Timer0 High register
   TL0 = 0;           // Init Timer0 Low register
   TMOD |= 0x25;                       // Timer0 in 16-bit mode, fuente externa    // Timer0 interrupt enabled
   TCON |= 0x50;                        // Timer0 ON
}

// void iniciar_timer2(void)
// {
//    TMR2CN |= 0x05;    // T2 en modo 16 bits, TR2 habilitado, clockeado por fuente externa
//    TMR2L = 0;
//    TMR2H = 0;
// }

void iniciar_contadorRPM(void) // usa timer3
{
	TMR3CN |= (1 << 7); //flag de overflow habilitada
	TMR3CN |= (1 << 2); //timer3 habilitado
	//clock interno / 12, en modo 16 bit auto-reload

    EIE1 |= 0x80; //habilitar interrupcion de timer3
    EIP1 |= 0x80; // dar prioridad a interrupcion de timer3

	TMR3L = 0;
    TMR3H = 0;

    TMR3RLL = 0; //parte alta y baja del valor de retorno de timer3.
    TMR3RLH = 0;
}

// void iniciar_PCA(void)
// {
// 	PCA0CN = 0x00;                      // Stop counter; clear all flags
// 	PCA0MD = 0x06;                      // la fuente de eventos proviene de flancos de bajada en ECI
// 	PCA0H = 0;
// 	PCA0L = 0;
// 	PCA0CN = 0x40;                      // Habilitar PCA

// }

void iniciar_osc_externo(void)
{
   OSCXCN |= 0x20; // seleccionar oscilador externo en modo CMOS Clock mode. Bits de control de frecuencia 0
}




/**
 * @brief inicia el PCA para el PWM
 * @details 
 */
void iniciar_PCA (void)
{
   XBR1 |= 0x01; // habilitar CEX0 en el crossbar
   // Configure PCA time base; overflow interrupt disabled
   PCA0CN = 0x00;                      // Stop counter; clear all flags
   PCA0MD = 0x08;                      // Use SYSCLK as time base

   PCA0CPM0 = 0xCB;                    // Module 0 = 16-bit PWM mode and
                                       // enable Module 0 Match and Interrupt
                                       // Flags

   // EIE1 |= 0x10;                       // Enable PCA interrupts

   // Start PCA counter
   CR = 1;
}

/**
 * @brief Establece el sistema en modo de bajo consumo
 * @details deja el clock interno activo y las interrupciones
 * pendientes, pero gastando mucha menos energia. El modo de bajo consumo se desactiva al momento de la llegada
 * de una interrupcion. Esta funcion hace que la unica interrupcion que hace volver al micro a su estado de consumo
 * normal es una interrupcion por UART, de manera que no se dispare automaticamente con una interrupcion de algun
 * timer. Para volver del modo bajo consumo, es necesario llamar a la funcion "deshabilitar_modo_bajo_consumo", ya 
 * que los parametros inhabilitados en esta funcion se vuelven a establecer en dicha funcion.
 * 
 * @return no devuelve ningun valor, pero si hace un envio por UART indicando que se inicio el modo de bajo consumo
 * 
 */
void habilitar_modo_bajo_consumo(void)
{
   int_aux1 = (char)IE;
   int_aux2 = (char)EIE1; //guardar los estados de los registros de interrupciones
   IE = 0;
   EIE1 = 0; // inhabilitar todas las interrupciones

   ES0 = 1; // habilitar interrupcion de UART
   EA = 1; // habilitar interrupciones

   printf("%05d", 800); // ack de modo de bajo consumo activado

   PCON |= 1;
}

/**
 * @brief vuelve del modo de bajo consumo y establece los registros de interrupcion inhabilitados antes de iniciar
 *  el modo de bajo consumo
 * 
 * @details El modo de bajo consumo se desactiva cuando el modulo de UART recibe un caracter, ya que se dejan habilitadas
 * las interrupciones del mismo, pero es necesario que se llame esta funcion para volver a establecer los parametros
 * necesarios con los que el sistema funciona, de otra manera el comportamiento se torna impredecible.
 * 
 * @return no devuelve ningun valor, pero si hace un envio por UART indicando que se desactivo el modo de bajo consumo
 * 
 */
void deshabilitar_modo_bajo_consumo(void)
{
   EA &= ~1; // deshabilitar interrupciones
   ES0 &= ~1; // deshabilitar interrupcion de UART

   IE = int_aux1;
   EIE1 = int_aux2; // reestablecemos los estados originales de los registros de interrupciones

   printf("%05d", 801); // ack de modo de bajo consumo desactivado
}