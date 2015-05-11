#include "minunit.h"
#include "../fuentes/headers.h"
#include "../fuentes/configurador.h"
#include "test_headers/test_configurador.h"

 int tests_run = 0; 
 int res;

 static char * test_cargar_single_ended() 
{
    cargar_single_ended(0);
    mu_assert("\nla funcion cargar_single_ended no cargo en pin 0\n", buffer_single[0] == 1);    
    cargar_single_ended(4);
    mu_assert("\nla funcion cargar_single_ended no cargo en pin 4\n", buffer_single[4] == 1);    
    cargar_single_ended(18);
    mu_assert("\nla funcion cargar_single_ended cargo en entrada incorrecta\n", buffer_single[0] == 0);    
    cargar_single_ended(-4);
    mu_assert("\nla funcion cargar_single_ended cargo en entrada incorrecta\n", buffer_single[0] == 0);

    return 0;
}
 
 
 static char * all_tests() {
    mu_run_test(test_cargar_single_ended);
     return 0;

 }
 
 int run_test_comunicacion(void) {

    // short int buffer_single_end[TAM_SINGLE] = malloc(TAM_SINGLE);

     char *result = all_tests();
     if (result != 0) {
         printf("%s\n", result);
     }
     else {
          // printf("TEST PASSED\n");
     } 
     return result != 0;
 }