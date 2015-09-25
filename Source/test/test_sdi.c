#include "minunit.h"
#include "../fuentes/headers.h"
#include "../fuentes/interfaz.h"

 int tests_run = 0; 
 int res;

struct shellstr *shell;

void iniciar_sysclock (void);
void iniciar_puertos (void);
void iniciar_UART(void);


static char * test_SDI()
{	
	shell->errn = 0;

// forma correcta
    shell->comando[0] = 'S';
    shell->comando[1] = 'D';
    shell->comando[2] = 'I';
    shell->args[0] = '4';
    shell->args[1] = ',';
    shell->args[2] = '1';
    shell->args[3] = '0';
    shell->args[4] = '0';

    shell->n_args = 5;
    analizar(shell);
    mu_assert("Forma correcta  \nNo deberia haber errores, pero si hay", shell->errn == 252);
    printf("Forma correcta - OK\n");
    shell->errn = 0;
    restart(shell);

    // argumento mayor al permitido
    shell->comando[0] = 'S';
    shell->comando[1] = 'D';
    shell->comando[2] = 'I';
    shell->args[0] = '9';
    shell->args[1] = ',';
    shell->args[2] = '4';

    shell->n_args = 3;
    analizar(shell);
    mu_assert("Argumento mayor al permitido  \nDeberia dar error 406 y no da", shell->errn == 406);
    printf("Argumento mayor al permitido - OK\n");
    shell->errn = 0;
    restart(shell);

    // argumento impar
    shell->comando[0] = 'S';
    shell->comando[1] = 'D';
    shell->comando[2] = 'I';
    shell->args[0] = '3';
    shell->args[1] = ',';
    shell->args[2] = '4';

    shell->n_args = 3;
    analizar(shell);
    mu_assert("Argumento impar  \nDeberia dar error 406 y no da", shell->errn == 406);
    printf("Argumento impar - OK\n");
    shell->errn = 0;
    restart(shell);

// sin especificar frecuencia
    shell->comando[0] = 'S';
    shell->comando[1] = 'D';
    shell->comando[2] = 'I';
    shell->args[0] = '4';

    shell->n_args = 1;
    analizar(shell);
    mu_assert("No especifica frecuencia  \nDeberia dar error 407 y no hay", shell->errn == 407);
    printf("No especifica frecuencia - OK\n");
    shell->errn = 0;
    restart(shell);

// con coma y sin sgeundo argumento
    shell->comando[0] = 'S';
    shell->comando[1] = 'D';
    shell->comando[2] = 'I';
    shell->args[0] = '4';
    shell->args[1] = ',';

    shell->n_args = 2;
    analizar(shell);    
    mu_assert("Error de sintaxis  \ndeberia dar error 408 y no hay", shell->errn == 408);
    printf("Error de sintaxis - OK\n");
    shell->errn = 0;
    restart(shell);

// demasiados argumentos
    shell->comando[0] = 'S';
    shell->comando[1] = 'D';
    shell->comando[2] = 'I';

    shell->n_args = 10;
    analizar(shell);
    mu_assert("Demasiados Argumentos  \ndeberia dar error 407 y no hay", shell->errn == 405);
    printf("Demasiados Argumentos - OK\n");
    shell->errn = 0;
    restart(shell);

// argumento fuera de rango
    shell->comando[0] = 'S';
    shell->comando[1] = 'D';
    shell->comando[2] = 'I';
    shell->args[0] = '4';
    shell->args[1] = ',';
    shell->args[2] = 'r';
    shell->args[3] = '8';
    shell->args[4] = '8';

    shell->n_args = 5;
    analizar(shell);
    mu_assert("Argumento fuera de rango 1  \ndeberia dar error 406 y no hay", shell->errn == 406);
    printf("Argumento fuera de rango 1 - OK\n");
    shell->errn = 0;
    restart(shell);

// argumento fuera de rango
    shell->comando[0] = 'S';
    shell->comando[1] = 'D';
    shell->comando[2] = 'I';
    shell->args[0] = '4';
    shell->args[1] = ',';
    shell->args[2] = '8';
    shell->args[3] = 'r';
    shell->args[4] = '8';

    shell->n_args = 5;
    analizar(shell);
    mu_assert("Argumento fuera de rango 2  \ndeberia dar error 406 y no hay", shell->errn == 406);
    printf("Argumento fuera de rango 2 - OK\n");
    shell->errn = 0;
    restart(shell);

// argumento fuera de rango
    shell->comando[0] = 'S';
    shell->comando[1] = 'D';
    shell->comando[2] = 'I';
    shell->args[0] = '4';
    shell->args[1] = ',';
    shell->args[2] = '8';
    shell->args[3] = '8';
    shell->args[4] = 'r';

    shell->n_args = 5;
    analizar(shell);
    mu_assert("Argumento fuera de rango 3  \ndeberia dar error 406 y no hay", shell->errn == 406);
    printf("Argumento fuera de rango 3 - OK\n");
    shell->errn = 0;
    restart(shell);

// argumento fuera de rango
    shell->comando[0] = 'S';
    shell->comando[1] = 'D';
    shell->comando[2] = 'I';
    shell->args[0] = '4';
    shell->args[1] = ',';
    shell->args[2] = '8';
    shell->args[3] = '0';
    shell->args[4] = '0';

    shell->n_args = 5;
	analizar(shell);
    // printf("%d\n",(shell->args[2] - '0')*100 + (shell->args[3] - '0')*10 + shell->args[4] - '0');
    mu_assert("Argumento fuera de rango 4  \ndeberia dar error 406 y no hay", shell->errn == 406);
    printf("Argumento fuera de rango 4 - OK\n");
    shell->errn = 0;
    restart(shell);


	
	return 0;
}
 static char * all_tests() 
 {
    printf("------------------TESTS PARA COMANDO SDI----------------------\n");
    mu_run_test(test_SDI);
    printf("------------------FIN TESTS PARA COMANDO SDI----------------------\n");

    return 0;
 }
 
 int main(void) {

    char *result;
    PCA0MD &= ~0x40;   // WDTE = 0 (clear watchdog timer

    shell = (struct shellstr *) malloc(sizeof(struct shellstr));

    iniciar_sysclock ();
    iniciar_puertos ();
    iniciar_UART();

    result = all_tests();

     if (result != 0) {
         printf("%s\n", result);
     }
     else {
          // printf("TEST PASDID\n");
     } 

     while(1);


     return result != 0;

 }

 void iniciar_UART(void)
{

//-----------------------------------------------------------------------------
// UART0_Init
//-----------------------------------------------------------------------------
//
// Configure the UART0 using Timer1, for <BAUDRATE> and 8-N-1.
//
   
   XBR0     |= 0x01;                    // Enable UART to Pins P0.4, P0.5
   XBR1     |= 0x40;                    // Enable Crossbar 

   P0SKIP   = 0x00;                    // Skip No Port Pins
   P0MDOUT |= 0x10;                    // Enable UTX as push-pull output
   P0MDIN  |= 0x20;                    // Enable URX pin as digital input.
   
   
   
   SCON0 = 0x10;                       // SCON0: 8-bit variable bit rate
                                       //        level of STOP bit is ignored
                                       //        RX enabled
                                       //        ninth bits are zeros
                                       //        clear RI0 and TI0 bits
   if (SYSCLK/BAUDRATE/2/256 < 1) {
      TH1 = -(SYSCLK/BAUDRATE/2);
      CKCON |=  0x08;                  // T1M = 1; SCA1:0 = xx
   } else if (SYSCLK/BAUDRATE/2/256 < 4) {
      TH1 = -(SYSCLK/BAUDRATE/2/4);
      CKCON &= ~0x0B;                  // T1M = 0; SCA1:0 = 01                  
      CKCON |=  0x01;
   } else if (SYSCLK/BAUDRATE/2/256 < 12) {
      TH1 = -(SYSCLK/BAUDRATE/2/12);
      CKCON &= ~0x0B;                  // T1M = 0; SCA1:0 = 00
   } else {
      TH1 = -(SYSCLK/BAUDRATE/2/48);
      CKCON &= ~0x0B;                  // T1M = 0; SCA1:0 = 10
      CKCON |=  0x02;
   }

   TL1 = TH1;                          // init Timer1
   TMOD &= ~0xf0;                      // TMOD: timer 1 in 8-bit autoreload
   TMOD |=  0x20;                       
   TR1 = 1;                            // START Timer1
   TI0 = 1;                            // Indicate TX0 ready


}

void iniciar_puertos (void)
{
   XBR1     |= 0x40;                    // Habilitar el crossbar
   P0MDOUT |= 0x10;                    // Habilitar UTX como push-pull output
     P1MDOUT |= 0x02;                                        // Habilitar led P1.1 como push pull
   // P0MDIN |= 0x0C;                  // P0.3 y P0.4 tienen que ser entrada digital
}

void iniciar_sysclock (void)
{
   OSCICN |= 0x03;                     // configuracion del oscilador para la maxima frecuencia
   RSTSRC  = 0x04;                     // Enable missing clock detector
   CLKSEL = 0x00;                      // selecciona el clock interno como fuente para SYSCLK

}