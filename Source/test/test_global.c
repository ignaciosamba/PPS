#include "minunit.h"
#include "../fuentes/headers.h"
#include "../fuentes/configurador.h"
#include "test_headers/test_comunicacion.h"
#include "test_headers/test_memoria.h"

 bit f_dato_convertido;
 char bdata buffer_single;
 sbit buffer_single_0 = buffer_single ^ 0;
 sbit buffer_single_1 = buffer_single ^ 1;
 sbit buffer_single_2 = buffer_single ^ 2;
 sbit buffer_single_3 = buffer_single ^ 3;
 sbit buffer_single_4 = buffer_single ^ 4;
 sbit buffer_single_5 = buffer_single ^ 5;
 sbit buffer_single_6 = buffer_single ^ 6;
 sbit buffer_single_7 = buffer_single ^ 7;

 
 void main(void) 
 {
    short int tests_run = 0;
    short int errores = 0;
    short int err;
    short int i = 0;

    PCA0MD &= ~0x40;                    // WDTE = 0 (clear watchdog timer 

    // for (i=0 ; i < 8 ; i++)
        buffer_single = 0;

    iniciar_puertos();
    iniciar_sysclock();
    iniciar_UART();

    if((err = run_test_comunicacion()) != 1)
    {
        printf("error en comunicacion.c\n");
        errores++;
    }
    tests_run++;
    if((err = run_test_configurador()) != 1)
    {
        printf("error en configurador.c\n");
        errores++;
    }
    tests_run++;
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