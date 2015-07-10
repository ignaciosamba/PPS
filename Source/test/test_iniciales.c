#include "minunit.h"
#include "../fuentes/headers_hw.h"
#include "../fuentes/headers_logic.h"
#include "../fuentes/configurador.h"

 int tests_run = 0; 
 // int res;

sbit LED = P0^7;
int aux;
int aux2;
bool f_UART_R;
bool f_UART_T;

void Timer2_Init (int counts);

static char * test_BLINKLED()
{   

    Timer2_Init (SYSCLK / 6 / 1);        // Iniciar timer2 para que interrumpa a 12 Hz
    EA = 1;                                          // enable global interrupts

    aux = 1000;
    while(aux > 0)
    {
        aux--;
    }

    EA = 0;
    Timer2_Init (SYSCLK / 8 / 1);        // Iniciar timer2 para que interrumpa a 12 Hz
    EA = 1;

    aux = 1000;
    while(aux > 0)
    aux--;


    EA = 0;
    LED = 0;


    return 0;
}



static char * test_UART() 
{ 
    
    iniciar_UART();
    f_UART_R = false;
    f_UART_T = false;

    EA = 1;
    ES0 = 1; // habilitar interrupcion de UART
    printf("---------------TESTS BASICOS ----------------\n");
    if(f_UART_T == false)
    {
        while(1)
        {
            aux = 100;
            while(aux != 0)
                aux--;

            LED = ~LED;
        }
    }
    else TI0 = 0;

    printf("presione cualquier tecla...\n");
    getchar();
    mu_assert("error en recepcion de datos de la UART", f_UART_R == 1);
    
    return 0;
}

static char * test_ADC() 
{ 
    iniciar_ADC();

    AD0INT = 0;     // se inicializa en 0 el bit de conversion completa del ADC 
    ADC0MUX = 0x08;  // el primer pin a analizar es el pin 0 en modo single-ended
    ADC0MD = 0x83;  // Habilitar conversion en modo continuo

    aux = 10000;
    while(aux != 0)
        aux--;
    mu_assert("El ADC no interrumpe", AD0INT == 1);
        
    return 0;
}





 static char * all_tests() {
    // mu_run_test(test_BLINKLED);
    mu_run_test(test_UART);
    printf("test_UART_OK\n");
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


void Timer2_Init (int counts)
{
   TMR2CN  = 0x00;                        // Stop Timer2; Clear TF2;
                                          // use SYSCLK/12 as timebase
   CKCON  &= ~0x60;                       // Timer2 clocked based on T2XCLK;

   TMR2RL  = -counts;                     // Init reload values
   TMR2    = 0xffff;                      // set to reload immediately
   ET2     = 1;                           // enable Timer2 interrupts
   TR2     = 1;                           // start Timer2
}


void Timer2_ISR (void) interrupt 5
{
   TF2H = 0;                              // clear Timer2 interrupt flag
   LED = ~LED;                            // change state of LED
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