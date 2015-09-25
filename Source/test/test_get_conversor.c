#include "minunit.h"
#include "../fuentes/headers.h"
#include "../fuentes/interfaz.h"
#include "../fuentes/configurador.h"

 int tests_run = 0; 
 int res;
 short int flag;
 short int bandera_dif;

struct shellstr *shell;

static char * test_GDI()
{	
	shell->errn = 0;

// forma correcta
    shell->comando[0] = 'G';
    shell->comando[1] = 'D';
    shell->comando[2] = 'I';
    shell->args[0] = '4';

    shell->n_args = 1;
    analizar(shell);
    mu_assert("Forma correcta  \nNo deberia dar errores, pero si da", shell->errn == 0);
    printf("Forma correcta  -------  OK\n");
    shell->errn = 0;
    restart(shell);

// Argumento impar
    shell->comando[0] = 'G';
    shell->comando[1] = 'D';
    shell->comando[2] = 'I';
    shell->args[0] = '3';

    shell->n_args = 1;
    analizar(shell);
    mu_assert("Argumento impar  \nNo deberia dar errores, pero si da", shell->errn == 406);
    printf("Argumento impar  -------  OK\n");
    shell->errn = 0;
    restart(shell);

    // argumento mayor al permitido
    shell->comando[0] = 'G';
    shell->comando[1] = 'D';
    shell->comando[2] = 'I';
    shell->args[0] = '9';

    shell->n_args = 1;
    analizar(shell);
    mu_assert("Argumento mayor al permitido  \nDeberia dar error 406 y no da", shell->errn == 406);
    printf("Argumento mayor al permitido  -------  OK\n");
    shell->errn = 0;
    restart(shell);

// demasiados argumentos
    shell->comando[0] = 'G';
    shell->comando[1] = 'D';
    shell->comando[2] = 'I';

    shell->n_args = 10;
    analizar(shell);
    mu_assert("Demasiados argumentos  \ndeberia dar error 407 y no da", shell->errn == 405);
    printf("Demasiados argumentos  -------  OK\n");
    shell->errn = 0;
    restart(shell);

	return 0;
}

static char * test_GSE()
{   
    shell->errn = 0;

// forma correcta
    shell->comando[0] = 'G';
    shell->comando[1] = 'S';
    shell->comando[2] = 'E';
    shell->args[0] = '4';

    shell->n_args = 1;
    analizar(shell);
    mu_assert("Forma correcta  \nNo deberia dar errores, pero si da", shell->errn == 0);
    printf("Forma correcta  -------  OK\n");
    shell->errn = 0;
    restart(shell);

    // argumento mayor al permitido
    shell->comando[0] = 'G';
    shell->comando[1] = 'S';
    shell->comando[2] = 'E';
    shell->args[0] = '9';

    shell->n_args = 1;
    analizar(shell);
    mu_assert("Argumento mayor al permitido  \nDeberia dar error 406 y no da", shell->errn == 406);
    printf("Argumento mayor al permitido  -------  OK\n");
    shell->errn = 0;
    restart(shell);

// demasiados argumentos
    shell->comando[0] = 'G';
    shell->comando[1] = 'S';
    shell->comando[2] = 'E';

    shell->n_args = 10;
    analizar(shell);
    mu_assert("Demasiados argumentos  \ndeberia dar error 407 y no da", shell->errn == 405);
    printf("Demasiados argumentos  -------  OK\n");
    shell->errn = 0;
    restart(shell);

    return 0;
}

static char * test_SHA()
{   
    shell->errn = 0;

// forma correcta
    shell->comando[0] = 'S';
    shell->comando[1] = 'H';
    shell->comando[2] = 'A';

    shell->n_args = 0;
    analizar(shell);
    mu_assert("Forma correcta  \nNo deberia dar errores, pero si da", shell->errn == 0);
    printf("Forma correcta  -------  OK\n");
    shell->errn = 0;
    restart(shell);

// con argumentos
    shell->comando[0] = 'S';
    shell->comando[1] = 'H';
    shell->comando[2] = 'A';

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
    printf("------------------TESTS PARA GETTERS DEL CONVERSOR----------------------\n");
    printf("-GSE-\n");
    mu_run_test(test_GSE);
    printf("-GSE OK-\n");
    printf("-GDI-\n");
    mu_run_test(test_GDI);
    printf("-GDI OK-\n");
    printf("-SHA-\n");
    mu_run_test(test_SHA);
    printf("-SHA OK-\n");
    printf("------------------FIN TESTS PARA GETTERS DEL CONVERSOR----------------------\n");

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
          // printf("TEST PAGDID\n");
     } 

     while(1);


     return result != 0;

 }