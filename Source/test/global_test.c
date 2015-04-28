#include "minunit.h"
#include "../fuentes/headers.h"
#include "../fuentes/configuracion.h"

 int tests_run = 0;
 int err;

 
 void main(void) {

    if((err = run_test_comunicacion()) != 1)
        printf("error en comunicacion.c\n");
    tests_run++;

 }