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
    // mu_assert("\n     error, nunca convirtio nada\n", 1);
    return 0;
}

static char * test_cargar_buffer_single()
{
    char bdata buffer = 0;
    char dato;

    dato = '0';
    buffer = cargar_buffer_single(&dato);
    mu_assert("\nla funcion cargar_buffer_single no cargo en pin 0\n", buffer_single ^ 0 == 1);    
    dato = '3';
    buffer = cargar_buffer_single(&dato);
    mu_assert("\nla funcion cargar_buffer_single no cargo en pin 4\n", buffer_single ^ 4 == 1);    
    dato = '0';
    buffer = cargar_buffer_single(&dato);
    mu_assert("\nla funcion cargar_buffer_single cargo en entrada incorrecta\n", buffer_single ^ 0 == 0);    
    dato = '0';
    buffer = cargar_buffer_single(&dato);
    mu_assert("\nla funcion cargar_buffer_single cargo en entrada incorrecta\n", buffer_single ^ 0 == 0);

    return 0;
}
 
 static char * all_tests() {
    iniciar_ADC();
    printf("test_pasar_datos_continuamente...\n");
    mu_run_test(test_pasar_datos_continuamente);
    printf("test_pasar_datos_continuamente_OK\n");
    printf("test_cargar_buffer_single\n");
    mu_run_test(test_cargar_buffer_single);
    printf("test_cargar_buffer_single_OK\n");
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