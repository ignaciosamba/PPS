#include "minunit.h"
#include "../fuentes/headers.h"
#include "../fuentes/configurador.h"
#include "test_headers/test_configurador.h"

 int tests_run = 0; 
 int res;

 static char * test_configurar1() 
{ 

    
    return 0;
}


 static char * all_tests() {
    mu_run_test(test_configurar1);
     return 0;

 }
 
 int run_test_configurador(void) {

     char *result = all_tests();
     if (result != 0) {
         printf("%s\n", result);
     }
     else {
          // printf("TEST PASSED\n");
     } 
     return result != 0;
 }