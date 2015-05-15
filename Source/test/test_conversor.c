#include "minunit.h"
#include "../fuentes/headers.h"
#include "../fuentes/conversor.h"
#include "../fuentes/configurador.h"
#include "test_headers/test_conversor.h"

 // int tests_run = 0; 
 // int res;

 static char * test_pasar_datos_continuamente() 
{   
    f_dato_convertido = 0;
    while(!f_dato_convertido);
    mu_assert("\n     error, nunca convirtio nada\n", 1);
    return 0;
}

static char * test_cargar_buffer_single()
{
    cargar_buffer_single(0);
    mu_assert("\nla funcion cargar_buffer_single no cargo en pin 0\n", buffer_single ^ 0 == 1);    
    cargar_buffer_single(4);
    mu_assert("\nla funcion cargar_buffer_single no cargo en pin 4\n", buffer_single ^ 4 == 1);    
    cargar_buffer_single(18);
    mu_assert("\nla funcion cargar_buffer_single cargo en entrada incorrecta\n", buffer_single ^ 0 == 0);    
    cargar_buffer_single(-4);
    mu_assert("\nla funcion cargar_buffer_single cargo en entrada incorrecta\n", buffer_single ^ 0 == 0);
}
 
 static char * all_tests() {
    iniciar_ADC();
    mu_run_test(test_pasar_datos_continuamente);
    mu_run_test(test_cargar_buffer_single);
     return 0;

 }
 
 int run_test_conversor(void) {

    char *result = all_tests();

    if (result != 0) {
     printf("%s\n", result);
    }
    else {
      // printf("TEST PASSED\n");
    } 
    return result != 0;

 }