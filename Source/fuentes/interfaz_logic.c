#include "headers_logic.h"
#include "interfaz_logic.h"

char obtener_entrada(struct shellstr *shell)
{
    char i = 0;
	printf("MML>"); // prints out the prompt
    while((shell->entrada = getchar()) != ',')
    {
        if(shell->entrada == '\n') break;

        if(i < TAM_COMANDO)
        {
            shell->comando[i] = shell->entrada;
            i++;
        }
        else shell->errn = 404;
    }

    i = 0;

    if(shell->entrada != '\n')
    while((shell->entrada = getchar()) != '\n')
    {
        if(i < MAX_ARGS)
        {
            shell->args[i] = shell->entrada;
            i++;
        }
        else shell->errn = 405;
    }

    shell->n_args = i;
    if(shell->n_args > 7)

    if(shell->entrada != '\n')
    while (getchar() != '\n');


    if(shell->errn != 0)
    {
        // printf("dio error!!, error: %hu\n", shell->errn);
        return 0;
    }
    // printf("no dio error!!\n");
	// shell = parsear_entrada(shell);													
	// shell = analizar(shell); 

	// if(shell->report != 0)
	// 	report(shell->report);
	// shell->report = 0;

	// restart(shell);

	return 0;
}

void restart(struct shellstr *shell)
{       
    int i;
    for (i = 0; i < 8;i++)
        shell->args[i] = 0;
}

struct shellstr *analizar(struct shellstr *shell)
{

	if((shell->comando[0] == 'S') && (shell->comando[1] == 'S') && (shell->comando[2] == 'E'))
        // printf("comando: SSE\n");

    else shell->errn = 404;

	return shell;

}


void reportar(short int e)
{
    switch(e)
    {
        case 404: printf("ERROR 404: comando no encontrado\n");
        case 405: printf("ERROR 405: demasiados argumentos\n");
    }
}



void printeartodo(struct shellstr *shell)
{
    int i;

    for(i = 0; i<TAM_COMANDO; i++)
    {
        printf("%c", shell->comando[i]);
    }
    for(i = 0; i<shell->n_args; i++)
    {
        printf("%c", shell->args[i]);
    }

}