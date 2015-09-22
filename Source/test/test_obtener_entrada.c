#include "minunit.h"
#include "../fuentes/headers.h"
#include "../fuentes/interfaz.h"
#include "../fuentes/configurador.h"

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

    printf("SSE,245\n");
	obtener_entrada(shell);
	mu_assert("Error. hubo errores y no deberia haber", shell->errn == 0);	
    shell->errn = 0;
    restart(shell);

    printf("ABC,123\n");
	obtener_entrada(shell);
	mu_assert("Error. el comando esta mal, pero igual no deberia haber errores", shell->errn == 0);
    shell->errn = 0;
    restart(shell);

    printf("ABCDEFG\n");
	obtener_entrada(shell);
	mu_assert("Error. deberia haber error 404 y no hay(1)", shell->errn == 404);
    shell->errn = 0;
    restart(shell);

    printf("AAA,123456789\n");
	obtener_entrada(shell);
	mu_assert("Error. deberia haber error 405 y no hay(2)", shell->errn == 405);
    shell->errn = 0;
    restart(shell);
	return 0;
}

 static char * all_tests() 
 {
    printf("------------------TESTS DE OBTENCION DE ENTRADA----------------------\n\n");

    mu_run_test(test_obtener_entrada);

    printf("------------------FIN TESTS DE OBTENCION DE ENTRADA----------------------\n\n");

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