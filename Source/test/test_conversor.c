#include "minunit.h"
#include "../fuentes/headers.h"
#include "../fuentes/configurador.h"
#include "test_headers/test_conversor.h"

 int tests_run = 0; 
 int res;

 static char * test_pasar_datos_continuamente() 
{   
    dato_convertido = 0;
    while(!dato_convertido);
    mu_assert("\n     error, nunca convirtio nada\n", 1);
    return 0;
}
 
 
 static char * all_tests() {
    mu_run_test(test_pasar_datos_continuamente);
     return 0;

 }
 
 int run_test_conversor(void) {

    iniciar_ADC();

    char *result = all_tests();
    if (result != 0) {
     printf("%s\n", result);
    }
    else {
      // printf("TEST PASSED\n");
    } 
    return result != 0;

 }