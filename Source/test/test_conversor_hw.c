#include "minunit.h"
#include "../fuentes/headers_hw.h"
#include "../fuentes/headers_logic.h"
#include "../fuentes/conversor_hw.h"

int tests_run = 0; 
int res;
int count;
short int bandera_dif;
bool f_dato_convertido;

struct shellstr *shell;

int iniciar_UART(void);
void iniciar_puertos (void);
void iniciar_sysclock (void);
int iniciar_ADC(void);

void ADC0_ISR (void) interrupt 10
{
   // printf("hola, acabo de convertir\n");
   while(!AD0INT);                     // Wait till conversion complete
   AD0INT = 0;                         // Clear ADC0 conversion complete flag
   f_dato_convertido = true;
   count++;
   // LED = ~LED;
}

static char * test_cambiar_pin()
{
    ADC0MUX = 0x08;
    cambiar_pin();
    mu_assert("error en cambiar_pin, ADC0MUX deberia ser 0x18\n", ADC0MUX == 0x18);
    ADC0MUX = 0x18;
    cambiar_pin();
    mu_assert("error en cambiar_pin, ADC0MUX deberia ser 0x28\n", ADC0MUX == 0x28);
    ADC0MUX = 0x28;
    cambiar_pin();
    mu_assert("error en cambiar_pin, ADC0MUX deberia ser 0x38\n", ADC0MUX == 0x38);
    ADC0MUX = 0x38;
    cambiar_pin();
    mu_assert("error en cambiar_pin, ADC0MUX deberia ser 0x48\n", ADC0MUX == 0x48);
    ADC0MUX = 0x48;
    cambiar_pin();
    mu_assert("error en cambiar_pin, ADC0MUX deberia ser 0x58\n", ADC0MUX == 0x58);
    ADC0MUX = 0x58;
    cambiar_pin();
    mu_assert("error en cambiar_pin, ADC0MUX deberia ser 0x68\n", ADC0MUX == 0x68);
    ADC0MUX = 0x68;
    cambiar_pin();
    mu_assert("error en cambiar_pin, ADC0MUX deberia ser 0x78\n", ADC0MUX == 0x78);
    ADC0MUX = 0x78;
    cambiar_pin();
    mu_assert("error en cambiar_pin, ADC0MUX deberia ser 0x01\n", ADC0MUX == 0x01);
    ADC0MUX = 0x01;
    cambiar_pin();
    mu_assert("error en cambiar_pin, ADC0MUX deberia ser 0x23\n", ADC0MUX == 0x23);
    ADC0MUX = 0x23;
    cambiar_pin();
    mu_assert("error en cambiar_pin, ADC0MUX deberia ser 0x45\n", ADC0MUX == 0x45);
    ADC0MUX = 0x45;
    cambiar_pin();
    mu_assert("error en cambiar_pin, ADC0MUX deberia ser 0x67\n", ADC0MUX == 0x67);
    ADC0MUX = 0x67;
    cambiar_pin();
    mu_assert("error en cambiar_pin, ADC0MUX deberia ser 0x08\n", ADC0MUX == 0x08);

    return 0;
}

static char * test_conf_ganancia()
{
    ADC0CN = 0x01;
    shell->args[0] = '0';
    conf_ganancia(shell);
    mu_assert("error en conf_ganancia, ADC0CN deberia ser 0x00\n", (ADC0CN & 0x0F) == 0x00);
    shell->args[0] = '1';
    conf_ganancia(shell);
    mu_assert("error en conf_ganancia, ADC0CN deberia ser 0x01\n", (ADC0CN & 0x0F) == 0x01);
    shell->args[0] = '2';
    conf_ganancia(shell);
    mu_assert("error en conf_ganancia, ADC0CN deberia ser 0x02\n", (ADC0CN & 0x0F) == 0x02);
    shell->args[0] = '3';
    conf_ganancia(shell);
    mu_assert("error en conf_ganancia, ADC0CN deberia ser 0x03\n", (ADC0CN & 0x0F) == 0x03);
    shell->args[0] = '4';
    conf_ganancia(shell);
    mu_assert("error en conf_ganancia, ADC0CN deberia ser 0x04\n", (ADC0CN & 0x0F) == 0x04);
    shell->args[0] = '5';
    conf_ganancia(shell);
    mu_assert("error en conf_ganancia, ADC0CN deberia ser 0x05\n", (ADC0CN & 0x0F) == 0x05);
    shell->args[0] = '6';
    conf_ganancia(shell);
    mu_assert("error en conf_ganancia, ADC0CN deberia ser 0x06\n", (ADC0CN & 0x0F) == 0x06);
    shell->args[0] = '7';
    conf_ganancia(shell);
    mu_assert("error en conf_ganancia, ADC0CN deberia ser 0x07\n", (ADC0CN & 0x0F) == 0x07);


    shell->args[0] = '8';
    conf_ganancia(shell);
    mu_assert("error en conf_ganancia, errn deberia ser 407\n",shell->errn = 407);    
    shell->args[0] = '9';
    conf_ganancia(shell);
    mu_assert("error en conf_ganancia, errn deberia ser 407\n",shell->errn = 407);    

    return 0;
}

static char * test_analizar_buffer()
{
    ADC0MUX = 0x08;
    shell->buffer_adc[0] = 1;
    mu_assert("error en analizar_buffer con ADC0MUX = 0x08 e indice 0, deberia ser 1\n",analizar_buffer(shell));  
    ADC0MUX = 0x18;
    shell->buffer_adc[1] = 1;
    mu_assert("error en analizar_buffer con ADC0MUX = 0x18 e indice 1, deberia ser 1\n",analizar_buffer(shell));  
    ADC0MUX = 0x28;
    shell->buffer_adc[2] = 1;
    mu_assert("error en analizar_buffer con ADC0MUX = 0x28 e indice 2, deberia ser 1\n",analizar_buffer(shell));  
    ADC0MUX = 0x38;
    shell->buffer_adc[3] = 1;
    mu_assert("error en analizar_buffer con ADC0MUX = 0x38 e indice 3, deberia ser 1\n",analizar_buffer(shell));  
    ADC0MUX = 0x48;
    shell->buffer_adc[4] = 1;
    mu_assert("error en analizar_buffer con ADC0MUX = 0x48 e indice 4, deberia ser 1\n",analizar_buffer(shell));  
    ADC0MUX = 0x58;
    shell->buffer_adc[5] = 1;
    mu_assert("error en analizar_buffer con ADC0MUX = 0x58 e indice 5, deberia ser 1\n",analizar_buffer(shell));  
    ADC0MUX = 0x68;
    shell->buffer_adc[6] = 1;
    mu_assert("error en analizar_buffer con ADC0MUX = 0x68 e indice 6, deberia ser 1\n",analizar_buffer(shell));  
    ADC0MUX = 0x78;
    shell->buffer_adc[7] = 1;
    mu_assert("error en analizar_buffer con ADC0MUX = 0x78 e indice 7, deberia ser 1\n",analizar_buffer(shell));  
    ADC0MUX = 0x01;
    shell->buffer_adc[8] = 1;
    mu_assert("error en analizar_buffer con ADC0MUX = 0x01 e indice 8, deberia ser 1\n",analizar_buffer(shell));  
    ADC0MUX = 0x23;
    shell->buffer_adc[9] = 1;
    mu_assert("error en analizar_buffer con ADC0MUX = 0x23 e indice 9, deberia ser 1\n",analizar_buffer(shell));  
    ADC0MUX = 0x45;
    shell->buffer_adc[10] = 1;
    mu_assert("error en analizar_buffer con ADC0MUX = 0x45 e indice 10, deberia ser 1\n",analizar_buffer(shell));  
    ADC0MUX = 0x67;
    shell->buffer_adc[11] = 1;
    mu_assert("error en analizar_buffer con ADC0MUX = 0x67 e indice 11; deberia ser 1\n",analizar_buffer(shell));

 
    ADC0MUX = 0x45;
    shell->buffer_adc[10] = 0;
    shell->var = 2;
    mu_assert("error en analizar_buffer con ADC0MUX = 0x45, indice 10 y valor 0, deberia ser 0\n",!analizar_buffer(shell));
    ADC0MUX = 0x45;
    shell->buffer_adc[10] = 100;
    shell->var = 2;
    mu_assert("error en analizar_buffer con ADC0MUX = 0x45, indice 10 y valor 100, deberia ser 0\n",!analizar_buffer(shell));
    ADC0MUX = 0x48;
    shell->buffer_adc[4] = 0;
    mu_assert("error en analizar_buffer con ADC0MUX = 0x48, indice 4 y valor 0 deberia ser 0\n",!analizar_buffer(shell));
    ADC0MUX = 0x48;
    shell->buffer_adc[4] = 100;
    mu_assert("error en analizar_buffer con ADC0MUX = 0x48, indice 4 y valor 100, deberia ser 0\n",!analizar_buffer(shell));
    ADC0MUX = 0x01;
    shell->buffer_adc[8] = 0;
    mu_assert("error en analizar_buffer con ADC0MUX = 0x01, indice 8 y valor 0 deberia ser 0\n",!analizar_buffer(shell));
    ADC0MUX = 0x01;
    shell->buffer_adc[8] = 100;
    mu_assert("error en analizar_buffer con ADC0MUX = 0x01, indice 8 y valor 100, deberia ser 0\n",!analizar_buffer(shell));

    return 0;
} 

static char * test_OWR()
{
    unsigned long int dato_a_enviar;
    char i = 30;
    count = 0;
    ADC0MUX = 0x08;

    while(i > 0)
    {
        if(f_dato_convertido)
        {
            f_dato_convertido = false;
            dato_a_enviar = convertir();
            if(analizar_buffer(shell))
            {
                enviar_dato(&dato_a_enviar);
            }
            cambiar_pin();
            i--;
            count--;
        }
    }
    printf("balance: %d\n", count);
    mu_assert("el OWR es demasiado alto", count == 0);



    return 0;
}

 static char * all_tests() 
 {
    printf("---------------TESTS DEL CONVERSOR ----------------\n");
    printf("test_cambiar_pin\n");
    mu_run_test(test_cambiar_pin);
    printf("test_cambiar_pin_OK\n");
    printf("test_conf_ganancia\n");
    mu_run_test(test_conf_ganancia);
    printf("test_conf_ganancia_OK\n");
    printf("test_analizar_buffer\n");
    mu_run_test(test_analizar_buffer);
    printf("test_analizar_buffer_OK\n");
    printf("test_OWR\n");
    mu_run_test(test_OWR);
    printf("test_OWR_OK\n");
    printf("---------------------- FIN ------------------------\n");

    return 0;
 }
 
 int main(void) {

    
    char *result;
    PCA0MD &= ~0x40;                    // WDTE = 0 (clear watchdog timer
    
    iniciar_sysclock ();
    iniciar_puertos ();
    iniciar_UART();
    iniciar_ADC();


    shell = (struct shellstr *) malloc(sizeof(struct shellstr));
    if(shell == NULL)
    {
        printf("no hay lugar para shell!\n");
    }

    AD0INT = 0;                         
    ADC0MUX = 0x08;
    ADC0MD = 0x83;                      // Start continuous conversions
    EA = 1;                             // Enable global interrupts

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


 int iniciar_UART(void)
{

    SCON0 = 0x10;                       // SCON0: 8-bit variable bit rate
                                       //        level of STOP bit is ignored
                                       //        RX enabled
                                       //        ninth bits are zeros
                                       //        clear RI0 and TI0 bits
    if (SYSCLK/BAUDRATE/2/256 < 1) 
    {
        TH1 = -(SYSCLK/BAUDRATE/2);
        CKCON &= ~0x0B;                  // T1M = 1; SCA1:0 = xx
        CKCON |=  0x08;
    } 
    else if (SYSCLK/BAUDRATE/2/256 < 4) 
    {
        TH1 = -(SYSCLK/BAUDRATE/2/4);
        CKCON &= ~0x0B;                  // T1M = 0; SCA1:0 = 01                  
        CKCON |=  0x01;
    } 
    else if (SYSCLK/BAUDRATE/2/256 < 12) 
    {
        TH1 = -(SYSCLK/BAUDRATE/2/12);
        CKCON &= ~0x0B;                  // T1M = 0; SCA1:0 = 00
    } 
    else 
    {
        TH1 = -(SYSCLK/BAUDRATE/2/48);
        CKCON &= ~0x0B;                  // T1M = 0; SCA1:0 = 10
        CKCON |=  0x02;
    }

    TL1 = TH1;                          // Init Timer1
    TMOD &= ~0xf0;                      // TMOD: timer 1 in 8-bit autoreload
    TMOD |=  0x20;                       
    ADC0MUX = 0x08;
    TR1 = 1;                            // START Timer1
    TI0 = 1;                            // Indicate TX0 ready

    return 0;
}

int iniciar_ADC(void)
{
    REF0CN |= 0x03;                     // Enable internal Vref
    ADC0CN = 0x00;                      // Gain = 1, Unipolar mode
    ADC0CF = 0x00;                      // Interrupts upon SINC3 filter output
                                       // and uses internal VREF

    ADC0CLK = (SYSCLK/MDCLK)-1;         // Generate MDCLK for modulator.
                                       // Ideally MDCLK = 2.4576MHz

    // Program decimation rate for desired OWR
    ADC0DEC = ((unsigned long) MDCLK / (unsigned long) OWR /
              (unsigned long) 128) - 1;

    ADC0BUF = 0x00;                     // Turn off Input Buffers
    ADC0MUX = 0x08;                     // Select AIN0.2

    ADC0MD = 0x81;                      // Start internal calibration
    while(AD0CALC != 1);                // Wait until calibration is complete

    EIE1   |= 0x08;                     // Enable ADC0 Interrupts
    ADC0MD  = 0x80;                     // Enable the ADC0 (IDLE Mode)
    
    return 0;
}

void iniciar_puertos (void)
{
   XBR0     = 0x01;                    // Habilitar UART en P0.4(TX) y P0.5(RX)                     
   XBR1     = 0x51;                    // Habilitar el crossbar, habilitar Timer0 y PCA
   P0MDOUT |= 0x10;                    // Habilitar UTX como push-pull output
   P0MDOUT |= 0x80;                    // Habilitar led P0.7 como push pull
   // P0MDIN |= 0x0C;                  // P0.3 y P0.4 tienen que ser entrada digital

}

void iniciar_sysclock (void)
{
   OSCICN |= 0x03;                     // configuracion del oscilador para la maxima frecuencia
   RSTSRC  = 0x04;                     // Enable missing clock detector
}

