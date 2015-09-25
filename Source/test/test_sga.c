#include "minunit.h"
#include "../fuentes/headers.h"
#include "../fuentes/interfaz.h"
#include "../fuentes/configurador.h"

 int tests_run = 0; 
 int res;
 short int flag;
 short int bandera_dif;

struct shellstr *shell;

static char * test_SGA()
{	
	shell->errn = 0;

// forma correcta
    shell->comando[0] = 'S';
    shell->comando[1] = 'G';
    shell->comando[2] = 'A';
    shell->args[0] = '4';

    shell->n_args = 1;
    analizar(shell);
    mu_assert("Forma correcta  \nNo deberia dar errores, pero si da", shell->errn == 0);
    printf("Forma correcta  -------  OK\n");
    shell->errn = 0;
    restart(shell);

    // argumento mayor al permitido
    shell->comando[0] = 'S';
    shell->comando[1] = 'G';
    shell->comando[2] = 'A';
    shell->args[0] = '9';

    shell->n_args = 1;
    analizar(shell);
    mu_assert("Argumento mayor al permitido  \nDeberia dar error 406 y no da", shell->errn == 406);
    printf("Argumento mayor al permitido  -------  OK\n");
    shell->errn = 0;
    restart(shell);

// demasiados argumentos
    shell->comando[0] = 'S';
    shell->comando[1] = 'G';
    shell->comando[2] = 'A';

    shell->n_args = 10;
    analizar(shell);
    mu_assert("Demasiados argumentos  \ndeberia dar error 407 y no da", shell->errn == 405);
    printf("Demasiados argumentos  -------  OK\n");
    shell->errn = 0;
    restart(shell);

	return 0;
}
 static char * all_tests() 
 {
    printf("------------------TESTS PARA COMANDO SGA----------------------\n");
    mu_run_test(test_SGA);
    printf("------------------FIN TESTS PARA COMANDO SGA----------------------\n");

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
          // printf("TEST PASGAD\n");
     } 

     while(1);


     return result != 0;

 }