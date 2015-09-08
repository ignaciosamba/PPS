#include <stdio.h>
#include "../headers.h"

#define PINCELDA 3
#define PINMOTOR 12
#define SETPOINT 40
#define PWMDEARRANQUE 1340

sbit PIN_PWM = P1^1;
sbit LED = P0^6;

volatile short int veces_pwm=0;
volatile short int velocidad=PWMDEARRANQUE;
short int cont_pwm=0;
short int variable=1000;
short int cantInt;
char f_PWM;
bool f_UART;

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

void iniciar_puertos (void)
{
	XBR0     = 0x01;                    // Habilitar UART en P0.4(TX) y P0.5(RX)                     
	XBR1     = 0x51;                    // Habilitar el crossbar, habilitar Timer0 y PCA
	P0MDOUT |= 0x10;                    // Habilitar UTX como push-pull output
	P1MDOUT |= 0x02;					// Habilitar el pin del motor P1.1 como push pull output
	// P0MDIN |= 0x0C;                  // P0.3 y P0.4 tienen que ser entrada digital


	P0MDOUT |= 0x40;					// Habilitar P0.6 el led como push pull
}

void iniciar_sysclock (void)
{
   OSCICN |= 0x03;                     // configuracion del oscilador para la maxima frecuencia
   RSTSRC  = 0x04;                     // Enable missing clock detector
}

void iniciar_arrancaMotor(void) // usa timer2
{
	TMR2CN |= (1 << 7); //flag de overflow habilitada
	TMR2CN |= (1 << 2); //timer2 habilitado
	//clock interno, en modo 16 bit auto-reload

    EIE1 |= 0x80; //habilitar interrupcion de timer2
    EIP1 |= 0x80; // dar prioridad a interrupcion de timer2

	TMR2L = 0;
    TMR2H = 0;

    //seteamos en 32758 el reload value para obtener mayor versatilidad en los tiempos de interrupcion
    TMR2RLL = 0; //parte baja del valor de retorno de timer2.
    TMR2RLH = 0x80; //parte alta del valor de retorno de timer2.

}

/**
 * @brief define cada cuanto se envia un pulso por la salida
 * @details setea el valor de frecuencia de envio de pulsos segun un numero ingresado que representa los microsegundos
 */
void set_cantInt(short int microsegundos)
{
	cantInt = 16129/microsegundos;
 /*
 *	siendo X = cantidad de veces que se interrumpe hasta que se levanta la bandera
 *	siendo Y = valor de retorno de timer2, fijo en 32768
 *	siendo Z = valor en uS del periodo para el generador de pulsos
 *
 *	se tiene que:
 *
 *	 	   10^6
 *   ------------------ = Z
 *   (SYSCLOCK / Y) * X
 *
 *   en esta funcion, Z se ingresa como parametro, y se obtiene X; y como Y = 32768,
 *     _______________
 *	  |               |
 *    |  X = 16129/Z  | 
 *    |_______________|
 *    
 */
}

void modificarPwm(short int microsegundos)
{
	set_cantInt(microsegundos); // cambio el valor de cantInt, y despues lo uso para contar las interrupciones y saber en cual me salgo.
	veces_pwm = 20000/microsegundos;
}

void arrancar_motor(void)
{
	int i;

	modificarPwm(1150);
	for(i = 1.5 * SYSCLK; i > 0; i--);
	modificarPwm(1299);
	for(i = 1.5 * SYSCLK; i > 0; i--);
	modificarPwm(PWMDEARRANQUE);
	for(i = 1.5 * SYSCLK; i > 0; i--);
}

//rutina de interrupcion de timer2
 void T2_ISR(void) interrupt 5
 {
 	TMR2CN &= ~(1 << 7); // volver a 0 la bandera de interrupcion del byte superior
 	TMR2CN &= ~(1 << 6); // volver a 0 la bandera de interrupcion del byte inferior
 	f_PWM = true; // se hablilita la bandera del timer
 }

void UART_ISR (void) interrupt 4
{
	if(RI0 == 1)
	{                         // Se borra el bit de dato recibido en la UART
		RI0 = 0;
		f_UART = true;
	}
//LED = ~LED;
}

void main()
{
   	int i = 0;
   	PCA0MD &= ~0x40;                    // deshabilitar el watchdog timer
   	iniciar_sysclock();
   	iniciar_puertos();
   	iniciar_UART();
   	printf("HOLA\n");
   	iniciar_arrancaMotor();
   	printf("lala\n");

   	// set_cantInt(1000);

   	//NO ESTA INTERRUMPIENDO.

   	while(1);
   	{
   		if(f_PWM)
   		{
   			LED = ~LED;
   			printf("interrupcion\n");
   		}
   	}

  //  	arrancar_motor();

  //  	while(1)
  //  	{

  //  		ES0 = 1; // habilitar interrupcion de UART
		// if (f_UART)
	 //    {
	 //    	EA = 0; // inhabilitar interrupciones globales
	 //    	f_UART = 0;
	 //    	velocidad =+ 20;
  //  			modificarPwm(velocidad);	
	 //    }
	 //    ES0 = 0;

  //  		if(f_PWM)
  //  		{
  //  			i++;
 	// 		f_PWM = 0; // se deshablilita la bandera del timer}
 	// 		if(i >= cantInt)
 	// 		{
 	// 			i = 0;

 	// 			  if(cont_pwm==(veces_pwm))
		// 		  {
		// 		      PIN_PWM = 1;
		// 		      cont_pwm=0; 
		// 		  }
		// 		  else
		// 		  {
		// 		      PIN_PWM = 0;
		// 		  }
		// 		  cont_pwm++;
 	// 		}


  //  		}   	
  //  	}




}