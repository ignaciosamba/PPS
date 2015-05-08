#include "minunit.h"
#include "../fuentes/headers.h"
#include "../fuentes/configurador.h"
#include "test_headers/test_comunicacion.h"
#include "test_headers/test_conversor.h"



 
 void main(void) 
 {
    int tests_run = 0;
    int errores = 0;
    int err;

    PCA0MD &= ~0x40;                    // WDTE = 0 (clear watchdog timer 


    iniciar_puertos();
    iniciar_sysclock();
    iniciar_UART();

    if((err = run_test_comunicacion()) != 1)
    {
        printf("error en comunicacion.c\n");
        errores++;
    }
    if((err = run_test_conversor()) != 1)
    {
        errores++;
    }
    tests_run++;

    printf("Tests corridos: %d\n", tests_run);
    printf("Errores: %d\n", errores);

    while(1);

 }