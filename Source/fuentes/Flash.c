#include "headers_hw.h"
#include "headers_logic.h"
#include "flash/F350_FlashPrimitives.h"
#include "flash/F350_FlashUtils.h"

void guardar_config(struct shellstr * shell) 
{
    char i;
    unsigned bytes_a_escribir;
	unsigned numbytes = 1;
    char src;
    FLADDR dest = 0x1b58;

    for (i= 0 ; i<8 ; i++)
    {
    	dest = dest + 1;
    	src = shell->buffer_adc[i];
        FLASH_Clear(dest, bytes_a_escribir);
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
    FLADDR src = 0x1b58;
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
    FLADDR src = 0x1b58;
    dest = 0;


    for (i=0 ; i<8 ; i++)
    {
        src = src + 1;
        FLASH_Read(&dest, src, numbytes);
        printf("%u\n", dest);
    }
}

void mostrar_config_actual(struct shellstr * shell)
{
    char i;
       for (i= 0 ; i<8 ; i++)
    {
        printf("%u\n", (int)shell->buffer_adc[i]/* - '0'*/);
    }

    printf("%c\n", (char)ADC0CN + '0');
}
