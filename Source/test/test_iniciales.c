#include "minunit.h"
#include "../fuentes/headers_hw.h"
#include "../fuentes/headers_logic.h"
#include "../fuentes/configurador.h"

 int tests_run = 0; 
 // int res;

sbit LED = P0^7;
unsigned int aux;
unsigned int aux2;
bool f_UART_R;
bool f_UART_T;


static char * test_UART() 
{ 
    
    iniciar_UART();
    // f_UART_R = false;
    // f_UART_T = false;

    // EA = 1;
    // ES0 = 1; // habilitar interrupcion de UART
    printf("---------------TESTS INICIALES ----------------\n");
    printf("test_UART\n");

    // if(f_UART_T == false)
    // {
    //     // OSCICN = 0x80;                         // oscilador interno a la minima frecuencia
    //     // Timer2_Init (SYSCLK / 24 / 1);        // Iniciar timer2 para que interrumpa a 12 Hz
    //     // EA = 1;
    //     while(1);
    // }
    // else TI0 = 0;

    printf("presione cualquier tecla...\n");
    mu_assert("\nerror en recepcion de datos de la UART", getchar() != NULL);
    
    return 0;
}

static char * test_ADC() 
{ 
    iniciar_ADC();

    AD0INT = 0;     // se inicializa en 0 el bit de conversion completa del ADC 
    ADC0MUX = 0x08;  // el primer pin a analizar es el pin 0 en modo single-ended
    ADC0MD = 0x83;  // Habilitar conversion en modo continuo

    aux = 1000000000;
    while(aux--);
    mu_assert("El ADC no interrumpe", AD0INT == 1);
        
    return 0;
}


 static char * all_tests() {
    mu_run_test(test_UART);
    printf("\ntest_UART_OK\n");
    printf("test_ADC\n");
    mu_run_test(test_ADC);
    printf("test_ADC_OK\n");
    printf("---------------------- FIN ------------------------\n");

     return 0;

 }
 
 int main(void) {

    char *result;
    PCA0MD &= ~0x40;                    // WDTE = 0 (clear watchdog timer
    
    iniciar_sysclock ();
    iniciar_puertos ();

    result = all_tests();


     if (result != 0) {
         printf("%s\n", result);
     }
     else {
          // printf("TEST PASSED\n");
     } 

     while(1);


     return result != 0;
 }





void UART_ISR (void) interrupt 4
{
   if(RI0 == 1)
   {                         // Se borra el bit de dato recibido en la UART
     RI0 = 0;
     f_UART_R = true;
   }
   if(TI0 == 1)
   {                         // Se borra el bit de dato recibido en la UART
     TI0 = 0;
     f_UART_T = true;
   }
   // LED = ~LED;
}