#include "minunit.h"
#include "../fuentes/headers_logic.h"
#include "../fuentes/conversor_logic.h"

 int tests_run = 0; 
 int res;
 short int bandera_dif;

struct shellstr *shell;

static char * test_cargar_buffer_single()
{
    char dato;

        


    return 0;
}

static char * test_cargar_buffer_dif()
{
    shell->buffer_adc = malloc(ARRAYSIZE);
    char dato;

    dato = '0';
    cargar_buffer_dif(shell, &dato);
    mu_assert("\nla funcion cargar_buffer_dif no cargo en pin 0\n", shell->buffer_adc[0] == 2);    
    dato = '2';
    cargar_buffer_dif(shell, &dato);
    mu_assert("\nla funcion cargar_buffer_dif no cargo en pin 2\n", shell->buffer_adc[2] == 2);    
    // dato = '0';
    // cargar_buffer_dif(shell, &dato);
    // mu_assert("\nla funcion cargar_buffer_dif cargo en entrada incorrecta\n", shell->buffer_adc[0] == 0);    
    // dato = '0';
    // cargar_buffer_dif(shell, &dato);
    // mu_assert("\nla funcion cargar_buffer_dif cargo en entrada incorrecta\n", shell->buffer_adc[0] == 0);

    return 0;
}

 
 static char * all_tests() 
 {
    printf("test_cargar_buffer_adc\n");
    mu_run_test(test_cargar_buffer_adc);
    printf("test_cargar_buffer_adc_OK\n");
    printf("test_cargar_buffer_dif\n");
    mu_run_test(test_cargar_buffer_dif);
    printf("test_cargar_buffer_dif_OK\n");
    return 0;
 }
 
 int main(void) {

    shell = (struct shellstr *) malloc(sizeof(struct shellstr));


    char *result = all_tests();

    if (result != 0) {
     printf("%s\n", result);
    }
    else {
      // printf("TEST PASSED\n");
    }

    free(shell);
    return result != 0;

 }