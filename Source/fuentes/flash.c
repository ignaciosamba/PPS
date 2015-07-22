#include "headers.h"
#include "flash/F350_FlashPrimitives.h"
#include "flash/F350_FlashUtils.h"


#define ADDR 0x01F0


void guardar_config(struct shellstr * shell) 
{
    char i;
    unsigned bytes_a_escribir = 9;
	unsigned numbytes = 1;
    char src;
    FLADDR dest = ADDR;
    // FLADDR page = 0x1B00;


    // FLASH_PageErase(page);
    FLASH_Clear(dest, bytes_a_escribir);
    
    for (i= 0 ; i<8 ; i++)
    {
        dest = dest + 1;
        src = shell->buffer_adc[i];
        FLASH_Write(dest, &src, numbytes);
    }

    dest = dest + 1;
    src = (char)ADC0CN;

    FLASH_Write(dest, &src, numbytes);

}

void cargar_config(struct shellstr * shell)
{
    char i;
	unsigned numbytes = 1;
    unsigned char dest;
    FLADDR src = ADDR;
    dest = 0;


    for (i=0 ; i<8 ; i++)
    {
    	src = src + 1;
    	FLASH_Read(&dest, src, numbytes);
    	shell->buffer_adc[i] = dest;
    }

    src= src + 1;
    FLASH_Read(&dest, src, numbytes);
    ADC0CN = dest;

}

void mostrar_config_flash()
{
    char i;
    unsigned numbytes = 1;
    unsigned char dest;
    FLADDR src = ADDR;
    dest = 0;


    for (i=0 ; i<8 ; i++)
    {
        src = src + 1;
        FLASH_Read(&dest, src, numbytes);
        printf("%u\n", (int)dest);
    }
}

void mostrar_config_actual(struct shellstr * shell)
{
    char i;
       for (i= 0 ; i<TAM_SINGLE ; i++)
    {
        printf("ADC[%i]: %u\n", (int)i, shell->buffer_adc_count[i]/* - '0'*/);
    }

    printf("ADC0CN: 0x%c\n", (char)ADC0CN + '0');
}
