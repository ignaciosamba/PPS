#include "headers_logic.h"
#include "conversor_logic.h"
#include "interfaz.h"

struct shellstr *obtener_entrada(struct shellstr *shell)
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
    for (i = 0; i < MAX_ARGS;i++)
        shell->args[i] = 0;
    for (i = 0; i < TAM_COMANDO;i++)
        shell->comando[i] = 0;
}

struct shellstr *analizar(struct shellstr *shell)
{
    if((shell->comando[0] == 'S') && (shell->comando[1] == 'T'))
    {
        shell->stop_conf = 1;
    }


    else if((shell->comando[0] == 'S') && (shell->comando[1] == 'S') && (shell->comando[2] == 'E'))
    {
        if(shell->n_args == 1)
        cargar_buffer_single(shell, &shell->args[0]);
        else shell->errn = 405;
    }
	else if((shell->comando[0] == 'S') && (shell->comando[1] == 'D') && (shell->comando[2] == 'I'))
    {
        if(shell->n_args == 1)
        cargar_buffer_dif(shell, &shell->args[0]);
        else shell->errn = 405;
    }
    else shell->errn = 404;

	return shell;

}


void reportar(struct shellstr *shell)
{
    switch(shell->errn)
    {   

        case 201: printf("\nACK 201: pin %c configurado exitosamente en modo single_ended\n", shell->args[0]);
        case 202: printf("\nACK 202: pines %c y %c configurados exitosamente en modo diferencial\n", shell->args[0], shell->args[0] + 1);
        case 404: printf("\nERROR 404: comando no encontrado\n");
        case 405: printf("\nERROR 405: demasiados argumentos\n");
        case 0: break;
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