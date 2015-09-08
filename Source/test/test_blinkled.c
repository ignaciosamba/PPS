#include "minunit.h"
#include "../fuentes/headers.h"
#include "../fuentes/configurador.h"

 int tests_run = 0; 

sbit LED = P1^1;
unsigned int aux;
unsigned int aux2;


void Timer2_Init (int counts);


static char * test_BLINKLED()
{   
    OSCICN = 0x80;                         // oscilador interno a la minima frecuencia

    Timer2_Init (SYSCLK / 24 / 1);        // Iniciar timer2 para que interrumpa a 12 Hz
    EA = 1;                                          // enable global interrupts

    aux2 = 5;
    aux = 1000000000;
    while(aux2--)
         while(aux--);
     EA = 0;

    Timer2_Init (SYSCLK / 12 / 1);        // Iniciar timer2 para que interrumpa a 12 Hz
    EA = 1;

    aux2 = 5;
    aux = 1000000000;
    while(aux2--)
         while(aux--);

    EA = 0;
    LED = 1;
    TR2 = 0;                           // stop Timer2
    

    OSCICN |= 0x03;                     // configuracion del oscilador para la maxima frecuencia

    return 0;
}


 static char * all_tests() {
    mu_run_test(test_BLINKLED);
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


 void Timer3_Init (int counts)
{
   TMR3CN  = 0x00;                        // Stop Timer3; Clear TF3;
                                          // use SYSCLK/13 as timebase
   CKCON  &= ~0xC0;                       // Timer3 clocked based on T3XCLK;

   TMR3RLH  = -counts & 0xFF000000;                     // Init reload values
   TMR3RLL  = -counts & 0x000000FF;                     // Init reload values
   TMR3H    = 0xff;                      // set to reload immediately
   TMR3L    = 0xff;                      // set to reload immediately
   ET3     = 1;                           // enable Timer3 interrupts
   TMR3CN |= 0x04;                           // TR3 = 1,  start Timer3
}


void Timer3_ISR (void) interrupt 5
{
   TF3H = 0;                              // clear Timer3 interrupt flag
   LED = ~LED;                            // change state of LED
}