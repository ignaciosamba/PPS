#include "minunit.h"
#include "../fuentes/headers_logic.h"
#include "../fuentes/interfaz.h"

 int tests_run = 0; 
 int res;
 short int flag;
 short int bandera_dif;

struct shellstr *shell;

static char * test_obtener_entrada()
{
    flag = false;
	//cada vez que se corre la funcion aca, agarra una linea nueva del archivo test_interfaz_comandos_de_prueba.txt
    printf("Ingrese los caracteres a medida que se piden. Al finalizar presione la tecla 'enter'\n");

    printf("SSE,245\n", );
	obtener_entrada(shell);
	mu_assert("Error. hubo errores y no deberia haber", shell->errn == 0);	
    shell->errn = 0;
    restart(shell);

    printf("ABCD,123\n", );
	obtener_entrada(shell);
	mu_assert("Error. el comando esta mal, pero igual no deberia haber errores", shell->errn == 0);
    shell->errn = 0;
    restart(shell);

    printf("ABCDEFG\n", );
	obtener_entrada(shell);
	mu_assert("Error. deberia haber error 404 y no hay(1)", shell->errn == 404);
    shell->errn = 0;
    restart(shell);

    printf("AAA,123456789\n", );
	obtener_entrada(shell);
	mu_assert("Error. deberia haber error 404 y no hay(2)", shell->errn == 404);
    shell->errn = 0;
    restart(shell);

    printf("SSE,245\n", );
	obtener_entrada(shell);
	mu_assert("Error. deberia haber error 405 y no hay", shell->errn == 405);

	return 0;
}

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
    mu_assert("no deberia haber errores, pero si hay", shell->errn == 251);
    shell->errn = 0;
    restart(shell);

// sin especificar frecuencia
    shell->comando[0] = 'S';
    shell->comando[1] = 'S';
    shell->comando[2] = 'E';
    shell->args[0] = '4';

    shell->n_args = 1;
    analizar(shell);
    mu_assert("deberia dar error 407 y no hay", shell->errn == 407);
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
    mu_assert("deberia dar error 408 y no hay", shell->errn == 407);
    shell->errn = 0;
    restart(shell);

// demasiados argumentos
    shell->comando[0] = 'S';
    shell->comando[1] = 'S';
    shell->comando[2] = 'E';

    shell->n_args = 10;
    analizar(shell);
    mu_assert("deberia dar error 408 y no hay", shell->errn == 407);
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
    mu_assert("deberia dar error 406 y no hay", shell->errn == 407);
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
    mu_assert("deberia dar error 406 y no hay", shell->errn == 407);
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
    mu_assert("deberia dar error 406 y no hay", shell->errn == 407);
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
    shell->args[4] = '8';

    shell->n_args = 5;
	analizar(shell);
	mu_assert("deberia dar error 406 y no hay", shell->errn == 407);
    shell->errn = 0;
    restart(shell);


	
	return 0;
}
 static char * all_tests() 
 {
    printf("------------------TESTS DE LA INTERFAZ----------------------\n");
    printf("test_obtener_entrada\n");
    mu_run_test(test_obtener_entrada);
    printf("\ntest_obtener_entrada_OK\n");
    printf("test_analizar\n");
    mu_run_test(test_analizar);
    printf("\ntest_analizar_OK\n");
    printf("------------------FIN TESTS DE LA INTERFAZ----------------------\n");

    return 0;
 }
 
 int main(void) {

    shell = (struct shellstr *) malloc(sizeof(struct shellstr));
    shell->buffer_adc = malloc(ARRAYSIZE);
    // shell->comando = malloc(TAM_COMANDO);
    // shell->args = malloc(MAX_ARGS);

    shell->errn = 0;

    // freopen("test_files/test_interfaz_comandos_de_prueba.txt", "r", stdin);


    char *result = all_tests();

    if (result != 0) {
     printf("%s\n", result);
    }
    else {
      // printf("TEST PASSED\n");
    }

    free(shell);
    return result != 0;

 }