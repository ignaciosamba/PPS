#include "minunit.h"
#include "../fuentes/headers_logic.h"
#include "../fuentes/interfaz.h"

 int tests_run = 0; 
 int res;
 short int bandera_dif;

struct shellstr *shell;

static char * test_obtener_entrada()
{
	//cada vez que se corre la funcion aca, agarra una linea nueva del archivo test_interfaz_comandos_de_prueba.txt
	
	obtener_entrada(shell);
	mu_assert("hubo errores y no deberia haber", shell->errn == 0);	
    shell->errn = 0;
    restart(shell);

	obtener_entrada(shell);
	mu_assert("el comando esta mal, pero igual no deberia haber errores", shell->errn == 0);
    shell->errn = 0;
    restart(shell);

	obtener_entrada(shell);
	mu_assert("deberia haber error 404 y no hay(1)", shell->errn == 404);
    shell->errn = 0;
    restart(shell);

	obtener_entrada(shell);
	mu_assert("deberia haber error 404 y no hay(2)", shell->errn == 404);
    shell->errn = 0;
    restart(shell);

	obtener_entrada(shell);
	mu_assert("deberia haber error 405 y no hay", shell->errn == 405);

	return 0;
}

static char * test_analizar()
{	

	shell->comando[0] = 'S';
	shell->comando[1] = 'S';
	shell->comando[2] = 'E';
	shell->args[0] = 4;

	shell->n_args = 1;
	shell->errn = 0;
	analizar(shell);
	mu_assert("no deberia haber errores, pero si hay", shell->errn == 251);
	
	return 0;
}
 static char * all_tests() 
 {
    printf("test_obtener_entrada\n");
    mu_run_test(test_obtener_entrada);
    printf("\ntest_obtener_entrada_OK\n");
    printf("test_analizar\n");
    mu_run_test(test_analizar);
    printf("\ntest_analizar_OK\n");
    return 0;
 }
 
 int main(void) {

    shell = (struct shellstr *) malloc(sizeof(struct shellstr));
    shell->buffer_single = malloc(ARRAYSIZE);
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