#include "minunit.h"
#include "../fuentes/headers_logic.h"
#include "../fuentes/conversor_logic.h"

 int tests_run = 0; 
 int res;
 short int bandera_dif;

struct shellstr *shell;

static char * test_cargar_buffer_single()
{
    shell->buffer_adc = malloc(ARRAYSIZE);
    char dato;

    dato = '0';
    cargar_buffer_adc(shell, &dato);
    mu_assert("\nla funcion cargar_buffer_adc no cargo en pin 0\n", shell->buffer_adc[0] == 1);    
    dato = '3';
    cargar_buffer_adc(shell, &dato);
    mu_assert("\nla funcion cargar_buffer_adc no cargo en pin 3\n", shell->buffer_adc[3] == 1);    
    // dato = '0';
    // cargar_buffer_adc(shell, &dato);
    // mu_assert("\nla funcion cargar_buffer_adc cargo en entrada incorrecta\n", shell->buffer_adc[0] == 0);    
    // dato = '0';
    // cargar_buffer_adc(shell, &dato);
    // mu_assert("\nla funcion cargar_buffer_adc cargo en entrada incorrecta\n", shell->buffer_adc[0] == 0);
    free(shell->buffer_adc);

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
    free(shell->buffer_adc);

    return 0;
}

static char * test_cambiar_pin()
{
    int i;
    shell->buffer_adc = malloc(ARRAYSIZE);
    for (i=0;i<ARRAYSIZE;i++)
        shell->buffer_adc[i] = 0;

    shell->buffer_adc[3] = 1;
    shell->buffer_adc[4] = 1;
    shell->buffer_adc[0] = 1;
    shell->posicion = 1;

    mu_assert("\nla funcion cambiar_pin no cambio al pin 3\n", cambiar_pin(shell) == 3);    


    free(shell->buffer_adc);

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
    printf("test_cambiar_pin\n");
    mu_run_test(test_cambiar_pin);
    printf("test_cambiar_pin_OK\n");
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