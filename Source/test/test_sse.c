#include "minunit.h"
#include "../fuentes/headers.h"
#include "../fuentes/interfaz.h"
#include "../fuentes/configurador.h"

 int tests_run = 0; 
 int res;
 
struct shellstr *shell;

static char * test_SSE()
{	
	shell->errn = 0;

// forma correcta
    shell->comando[0] = 'S';
    shell->comando[1] = 'S';
    shell->comando[2] = 'E';
    shell->args[0] = '4';
    shell->args[1] = ',';
    shell->args[2] = '1';
    shell->args[3] = '0';
    shell->args[4] = '0';

    shell->n_args = 5;
    analizar(shell);
    mu_assert("Forma correcta  \nNo deberia dar errores, pero si da", shell->errn == 251);
    printf("Forma correcta - OK\n");
    shell->errn = 0;
    restart(shell);

    // argumento mayor al permitido
    shell->comando[0] = 'S';
    shell->comando[1] = 'S';
    shell->comando[2] = 'E';
    shell->args[0] = '9';
    shell->args[1] = ',';
    shell->args[2] = '4';

    shell->n_args = 3;
    analizar(shell);
    mu_assert("Argumento mayor al permitido  \nDeberia dar error 406 y no da", shell->errn == 406);
    printf("Argumento mayor al permitido - OK\n");
    shell->errn = 0;
    restart(shell);

// sin especificar frecuencia
    shell->comando[0] = 'S';
    shell->comando[1] = 'S';
    shell->comando[2] = 'E';
    shell->args[0] = '4';

    shell->n_args = 1;
    analizar(shell);
    mu_assert("Sin especificar frecuencia  \nDeberia dar error 407 y no da", shell->errn == 407);
    printf("Sin especificar frecuencia - OK\n");
    shell->errn = 0;
    restart(shell);

// con coma y sin sgeundo argumento
    shell->comando[0] = 'S';
    shell->comando[1] = 'S';
    shell->comando[2] = 'E';
    shell->args[0] = '4';
    shell->args[1] = ',';

    shell->n_args = 2;
    analizar(shell);    
    mu_assert("Error de sintaxis  \ndeberia dar error 408 y no da", shell->errn == 408);
    printf("Error de sintaxis - OK\n");
    shell->errn = 0;
    restart(shell);

// demasiados argumentos
    shell->comando[0] = 'S';
    shell->comando[1] = 'S';
    shell->comando[2] = 'E';

    shell->n_args = 10;
    analizar(shell);
    mu_assert("Demasiados argumentos  \ndeberia dar error 407 y no da", shell->errn == 405);
    printf("Demasiados argumentos - OK\n");
    shell->errn = 0;
    restart(shell);

// argumento fuera de rango
    shell->comando[0] = 'S';
    shell->comando[1] = 'S';
    shell->comando[2] = 'E';
    shell->args[0] = '4';
    shell->args[1] = ',';
    shell->args[2] = 'r';
    shell->args[3] = '8';
    shell->args[4] = '8';

    shell->n_args = 5;
    analizar(shell);
    mu_assert("Argumento fuera de rango 1  \ndeberia dar error 406 y no da", shell->errn == 406);
    printf("Argumento fuera de rango 1 - OK\n");
    shell->errn = 0;
    restart(shell);

// argumento fuera de rango
    shell->comando[0] = 'S';
    shell->comando[1] = 'S';
    shell->comando[2] = 'E';
    shell->args[0] = '4';
    shell->args[1] = ',';
    shell->args[2] = '8';
    shell->args[3] = 'r';
    shell->args[4] = '8';

    shell->n_args = 5;
    analizar(shell);
    mu_assert("Argumento fuera de rango 2  \ndeberia dar error 406 y no da", shell->errn == 406);
    printf("Argumento fuera de rango 2 - OK\n");
    shell->errn = 0;
    restart(shell);

// argumento fuera de rango
    shell->comando[0] = 'S';
    shell->comando[1] = 'S';
    shell->comando[2] = 'E';
    shell->args[0] = '4';
    shell->args[1] = ',';
    shell->args[2] = '8';
    shell->args[3] = '8';
    shell->args[4] = 'r';

    shell->n_args = 5;
    analizar(shell);
    mu_assert("Argumento fuera de rango 3  \ndeberia dar error 406 y no da", shell->errn == 406);
    printf("Argumento fuera de rango 3 - OK\n");
    shell->errn = 0;
    restart(shell);

// argumento fuera de rango
    shell->comando[0] = 'S';
    shell->comando[1] = 'S';
    shell->comando[2] = 'E';
    shell->args[0] = '4';
    shell->args[1] = ',';
    shell->args[2] = '8';
    shell->args[3] = '0';
    shell->args[4] = '0';

    shell->n_args = 5;
	analizar(shell);
    // printf("%d\n",(shell->args[2] - '0')*100 + (shell->args[3] - '0')*10 + shell->args[4] - '0');
    mu_assert("Argumento fuera de rango 4  \ndeberia dar error 406 y no da", shell->errn == 406);
    printf("Argumento fuera de rango 4 - OK\n");
    shell->errn = 0;
    restart(shell);

	return 0;
}
 static char * all_tests() 
 {
    printf("------------------TESTS PARA COMANDO SSE----------------------\n");
    mu_run_test(test_SSE);
    printf("------------------FIN TESTS PARA COMANDO SSE----------------------\n");

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
          // printf("TEST PASSED\n");
     } 

     while(1);


     return result != 0;

 }