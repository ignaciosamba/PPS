#include "../fuentes/headers.h"
#include "minunit.h"
#include "../fuentes/flash/F350_FlashPrimitives.h"
#include "../fuentes/flash/F350_FlashUtils.h"
// #include "../fuentes/memoria.h"
#include "test_headers/test_memoria.h"
#include "headers_logic.h"

 static char * write() 
 {
 	unsigned numbytes = 1;
    // char *src = malloc(2);
    char src;
    FLADDR dest = 0x1b58;
    // src = 500;

    for (i= 0 ; i<8 ; i++)
    {
    	dest = dest + 1;
    	src = shell->buffer_adc[i];
    	FLASH_Write(dest, &src, numbytes);
    }

    dest = dest + 1;
    src = (char)ADC0CN;

    FLASH_Write(dest, &src, numbytes);
    // printf("la escritura no tuvo errores");

    return 0;
 }

 static char * read()
 {
 	unsigned numbytes = 1;
    // char *dest = malloc(numbytes);
    int dest;
    FLADDR src = 0x1b58;
    dest = 0;
    for (i=0 ; i<8 ; i++)
    {
    	src = src + 1;
    	FLASH_Read(&src, dest, numbytes);
    	shell->buffer_adc[i] = dest;
    }

    src= src + 1;
    FLASH_Read(&dest, src, numbytes);
    ADC0CN = dest;
    
    // printf("contenido en 0x1000: %d\n", dest);

    // mu_assert("la lectura no dio 500", dest == 500);

    // printf("la lectura no tuvo errores");
    return 0;
 }

