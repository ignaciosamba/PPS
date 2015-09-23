#include "minunit.h"
#include "../fuentes/headers.h"
#include "../fuentes/interfaz.h"
#include "../fuentes/configurador.h"

 int tests_run = 0; 
 int res;
 short int flag;
 short int bandera_dif;

struct shellstr *shell;

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
    mu_assert("SDI, args: 4,100  \nNo deberia haber errores, pero si hay", shell->errn == 252);
    printf("SDI, args: 4,100  -------  OK\n");
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
    mu_assert("SSE, args: 9,4  \nDeberia dar error 406 y no da", shell->errn == 406);
    printf("SSE, args: 4,9  -------  OK\n");
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
    mu_assert("SSE, args: 3,4  \nDeberia dar error 406 y no da", shell->errn == 406);
    printf("SSE, args: 3,4  -------  OK\n");
    shell->errn = 0;
    restart(shell);

// sin especificar frecuencia
    shell->comando[0] = 'S';
    shell->comando[1] = 'D';
    shell->comando[2] = 'I';
    shell->args[0] = '4';

    shell->n_args = 1;
    analizar(shell);
    mu_assert("SDI, args: 4  \nDeberia dar error 407 y no hay", shell->errn == 407);
    printf("SDI, args: 4  -------  OK\n");
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
    mu_assert("SDI, args: 4,  \ndeberia dar error 408 y no hay", shell->errn == 408);
    printf("SDI, args: 4,  -------  OK\n");
    shell->errn = 0;
    restart(shell);

// demasiados argumentos
    shell->comando[0] = 'S';
    shell->comando[1] = 'D';
    shell->comando[2] = 'I';

    shell->n_args = 10;
    analizar(shell);
    mu_assert("SDI, args: 10 argumentos  \ndeberia dar error 407 y no hay", shell->errn == 405);
    printf("SDI, args: 10 argumentos  -------  OK\n");
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
    mu_assert("SDI, args: 4,r88  \ndeberia dar error 406 y no hay", shell->errn == 406);
    printf("SDI, args: 4,r88  -------  OK\n");
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
    mu_assert("SDI, args: 4,8r8  \ndeberia dar error 406 y no hay", shell->errn == 406);
    printf("SDI, args: 4,8r8  -------  OK\n");
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
    mu_assert("SDI, args: 4,88r  \ndeberia dar error 406 y no hay", shell->errn == 406);
    printf("SDI, args: 4,88r  -------  OK\n");
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
    mu_assert("SDI, args: 4,800  \ndeberia dar error 406 y no hay", shell->errn == 406);
    printf("SDI, args: 4,800  -------  OK\n");
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