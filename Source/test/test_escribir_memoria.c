#include "../fuentes/headers_hw.h"
#include "../fuentes/headers_logic.h"
#include "../fuentes/configurador.h"
#include "minunit.h"
#include "../fuentes/flash/F350_FlashPrimitives.h"
#include "../fuentes/flash/F350_FlashUtils.h"
// #include "../fuentes/memoria.h"
// #include "test_headers/test_memoria.h"

 // int tests_run = 0; 
 // int res;

 static char * test_write() 
{
    unsigned numbytes = 2;
    // char *src = malloc(2);
    int src;
    FLADDR dest = 0x1B58;
    src = 8;

    FLASH_PageErase();
    FLASH_Write(dest, &src, numbytes);
    printf("la escritura no tuvo errores");

    return 0;
}

 static char * all_tests() {
    mu_run_test(test_write);
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