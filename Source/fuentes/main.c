/**
 * @file main.c
 * @author Sambataro, Ignacio; Mantovani, Luciano
 * @date 2015
 * @brief [brief description]
 * @details [long description]
 */
#include "headers.h"
#include "interfaz.h"
#include "configurador.h"
 

void main(void)
{

   	PCA0MD &= ~0x40;                    // WDTE = 0 (clear watchdog timer 


	iniciar_puertos();
	iniciar_sysclock();
	iniciar_UART();
	correr_menu();

	while(1);
}