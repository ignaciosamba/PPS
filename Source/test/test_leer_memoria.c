#include "../fuentes/headers_hw.h"
#include "../fuentes/configurador.h"
#include "../fuentes/headers_logic.h"
#include "minunit.h"
#include "../fuentes/flash/F350_FlashPrimitives.h"
#include "../fuentes/flash/F350_FlashUtils.h"
// #include "../fuentes/memoria.h"
#include "test_headers/test_memoria.h"

 // int tests_run = 0; 
 // int res;


  static char * test_read() 
{   
    unsigned numbytes = 2;
    // char *dest = malloc(numbytes);
    int dest;
    FLADDR src = 0x1b58;
    dest = 0;

    FLASH_Read(&dest, src, numbytes);
    printf("contenido en 0x1000: %d\n", dest);

    mu_assert("la lectura no dio 500", dest == 500);

    printf("la lectura no tuvo errores");
    return 0;
}
 

 static char * all_tests() {
    mu_run_test(test_read);
     return 0;

 }
 
 int main(void) {


    char *result;
    PCA0MD &= ~0x40;                    // WDTE = 0 (clear watchdog timer 
    iniciar_puertos();
    iniciar_sysclock();
    iniciar_UART();

     result = all_tests();
     if (result != 0) {
         printf("%s\n", result);
     }
     else {
          // printf("TEST PASSED\n");
     }

     while(1); 
     return result != 0;


 }