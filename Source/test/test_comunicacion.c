#include "minunit.h"
#include "../fuentes/headers.h"
#include "../fuentes/configuracion.h"

 int tests_run = 0; 
 int res;

 static char * test_UART() 
{ 
	// res = funcio();
    mu_assert("error, funcion_1 no respondio 10",res == 10);
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
          printf("TEST PASSED\n");
     } 
     return result != 0;
 }