#include "minunit.h"
#include "../fuentes/headers.h"
#include "../fuentes/interfaz.h"
#include "../fuentes/configurador.h"

 int tests_run = 0; 
 int res;
 short int flag;
 short int bandera_dif;

struct shellstr *shell;

static char * test_GT0()
{   
    shell->errn = 0;

// forma correcta
    shell->comando[0] = 'G';
    shell->comando[1] = 'T';
    shell->comando[2] = '0';

    shell->n_args = 0;
    analizar(shell);
    mu_assert("Forma correcta  \nNo deberia dar errores, pero si da", shell->errn == 0);
    printf("Forma correcta  -------  OK\n");
    shell->errn = 0;
    restart(shell);

// con argumentos
    shell->comando[0] = 'G';
    shell->comando[1] = 'T';
    shell->comando[2] = '0';

    shell->n_args = 1;
    analizar(shell);
    mu_assert("Demasiados argumentos  \ndeberia dar error 405 y no da", shell->errn == 405);
    printf("Demasiados argumentos  -------  OK\n");
    shell->errn = 0;
    restart(shell);

    return 0;
}

static char * test_GT2()
{	
	shell->errn = 0;

// forma correcta
    shell->comando[0] = 'G';
    shell->comando[1] = 'T';
    shell->comando[2] = '2';

    shell->n_args = 0;
    analizar(shell);
    mu_assert("Forma correcta  \nNo deberia dar errores, pero si da", shell->errn == 0);
    printf("Forma correcta  -------  OK\n");
    shell->errn = 0;
    restart(shell);

// con argumentos
    shell->comando[0] = 'G';
    shell->comando[1] = 'T';
    shell->comando[2] = '2';

    shell->n_args = 10;
    analizar(shell);
    mu_assert("Demasiados argumentos  \ndeberia dar error 405 y no da", shell->errn == 405);
    printf("Demasiados argumentos  -------  OK\n");
    shell->errn = 0;
    restart(shell);

	return 0;
}
 static char * all_tests() 
 {
    printf("------------------TESTS PARA FUNCIONES DE CONTADORES----------------------\n");
    printf("-GT0-\n");
    mu_run_test(test_GT0);
    printf("-GT0: OK-\n");
    printf("-GT2-\n");
    mu_run_test(test_GT2);
    printf("-GT2: OK-\n");
    printf("------------------FIN TESTS PARA FUNCIONES DE CONTADORES----------------------\n");

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
          // printf("TEST PAGT0D\n");
     } 

     while(1);


     return result != 0;

 }