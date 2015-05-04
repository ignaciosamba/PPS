#include "minunit.h"
#include "../fuentes/headers.h"
#include "../fuentes/configuracion.h"

 int tests_run = 0; 
 int res;

 static char * test_UART() 
{ 
    mu_assert("\n     error, iniciar_UART no devolvio 0\n", 0);
    return 0;
}
 
 
 static char * all_tests() {
    mu_run_test(test_UART);
     return 0;

 }
 
 int run_test_comunicacion(void) {

     char *result = all_tests();
     if (result != 0) {
         printf("%s\n", result);
     }
     else {
          // printf("TEST PASSED\n");
     } 
     return result != 0;
 }