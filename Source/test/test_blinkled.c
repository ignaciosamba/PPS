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