#include "minunit.h"
#include "../fuentes/headers.h"
#include "../fuentes/configurador.h"
#include "test_headers/test_comunicacion.h"
#include "test_headers/test_memoria.h"



 
 void main(void) 
 {
    int tests_run = 0;
    int errores = 0;
    int err;
    short int i = 0;

    PCA0MD &= ~0x40;                    // WDTE = 0 (clear watchdog timer 

    buffer_single [TAM_SINGLE] = malloc(TAM_SINGLE);
    for (i=0 ; i<0 ; i++)
        buffer_single[i]=0;

    iniciar_puertos();
    iniciar_sysclock();
    iniciar_UART();

    // if((err = run_test_comunicacion()) != 1)
    // {
    //     printf("error en comunicacion.c\n");
    //     errores++;
    // }
    // tests_run++;
    if((err = run_test_memoria()) != 1)
    {
        printf("error en memoria.c\n");
        errores++;
    }
    tests_run++;

    printf("Tests corridos: %d\n", tests_run);
    printf("Errores: %d\n", errores);

    while(1);

 }