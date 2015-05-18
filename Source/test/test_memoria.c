#include "minunit.h"
#include "../fuentes/headers.h"
#include "../fuentes/flash/F350_FlashPrimitives.h"
#include "../fuentes/flash/F350_FlashUtils.h"
// #include "../fuentes/memoria.h"
#include "test_headers/test_memoria.h"

 // int tests_run = 0; 
 // int res;

 static char * test_write() 
{
    unsigned numbytes = 2;
    char *src;/* = malloc(2);*/
    FLADDR dest = 0x1000;
    *src = 500;

    FLASH_Write(dest, src, numbytes);
    printf("la escritura no tuvo errores");

    return 0;
}

 static char * test_read() 
{   
    unsigned numbytes = 2;
    char *dest;/* = malloc(numbytes);*/
    FLADDR src = 0x1000;
    *dest = 0;

    dest = FLASH_Read(dest, src, numbytes);

    mu_assert("la lectura no dio 500", *dest == 500);

    printf("la lectura no tuvo errores");
    printf("contenido en 0x1000: %d\n", *dest);
    return 0;
}
 
 
 static char * all_tests() {
    printf("llego a run test memoria\n");
    mu_run_test(test_write);
    mu_run_test(test_read);
     return 0;

 }
 
 int run_test_memoria(void) {

     char *result = all_tests();
     if (result != 0) {
         printf("%s\n", result);
     }
     else {
          // printf("TEST PASSED\n");
     } 
     return result != 0;
 }