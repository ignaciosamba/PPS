#include "minunit.h"
#include "../fuentes/headers.h"
#include "../fuentes/configurador.h"
#include "../fuentes/conversor.h"
#include "test_headers/test_conversor.h"

 int tests_run = 0; 
 int res;
long int dato_a_enviar;
bool f_dato_convertido;


 static char * test_pasar_datos_continuamente() 
{   
    // dato_convertido = 0;
    // while(!dato_convertido);
    mu_assert("\n     error, nunca convirtio nada\n", 1);
    return 0;
}
 static char * test_gain() 
{

    while(1)
    {
        AD0INT = 0;                         
        ADC0MD = 0x83;                      // Start continuous conversions
        EA = 1;                             // Enable global interrupts
        // printf("no entraaa\n");
        if(f_dato_convertido)
        {
            // printf("AAAAAAAAAAAAAAA\n");
            f_dato_convertido = false;
            dato_a_enviar = convertir();
            enviar_dato(dato_a_enviar);
        }
    }

    return 0;
}
 
 
 static char * all_tests() {
    // mu_run_test(test_pasar_datos_continuamente);
    mu_run_test(test_gain);

     return 0;

 }
 
 int run_test_conversor(void) {

    // iniciar_ADC();

    char *result = all_tests();
    if (result != 0) {
     printf("%s\n", result);
    }
    else {
      // printf("TEST PASSED\n");
    } 
    return result != 0;

 }