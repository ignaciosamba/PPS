#include "headers_logic.h"
#include "conversor_logic.h"
#include "conversor_hw.h"
#include "flash.h"
#include "contador.h"
#include "interfaz.h"

struct shellstr *obtener_entrada(struct shellstr *shell)
{
    char i = 0;
	printf("MML>"); // imprime el prompt

    //recibe el comando
    while((shell->entrada = getchar()) != ',')
    {
        if(shell->entrada == '\n') {/*shell->errn = 0;*/ break;}

        if(i < TAM_COMANDO)  //la entrada debe ser menor al tamaño maximo de un comando
        {
            shell->comando[i] = shell->entrada;
            i++;
        }
        else shell->errn = 404;
    }

    i = 0;

    //recibe los argumentos
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

	return shell;
}

void restart(struct shellstr *shell)
{       
    int i;
    for (i = 0; i < MAX_ARGS;i++)
        shell->args[i] = 0;
    for (i = 0; i < TAM_COMANDO;i++)
        shell->comando[i] = 0;
    shell->errn = 0;
}

struct shellstr *analizar(struct shellstr *shell)
{
        // printf("lalalalalal\n");
    if((shell->comando[0] == 'S') && (shell->comando[1] == 'T'))
    {
        shell->stop_conf = 0;
    }


    else if((shell->comando[0] == 'S') && (shell->comando[1] == 'S') && (shell->comando[2] == 'E'))
    {
        if(shell->n_args > 1)
        {shell->errn = 405; return shell;}
        else if(shell->args[0] - '0' < 0 || shell->args[0] - '0' > 7)
        {shell->errn = 406; return shell;}

        cargar_buffer_single(shell, &shell->args[0]);
    }
    else if((shell->comando[0] == 'S') && (shell->comando[1] == 'D') && (shell->comando[2] == 'I'))
    {
        if(shell->n_args > 1)
        {shell->errn = 405; return shell;}
        else if(shell->args[0] - '0' < 0 || shell->args[0] - '0' > 6)
        {shell->errn = 406; return shell;}

        else cargar_buffer_dif(shell, &shell->args[0]);
    }
	else if((shell->comando[0] == 'S') && (shell->comando[1] == 'G') && (shell->comando[2] == 'A'))
    {
        if(shell->n_args > 1)
        {shell->errn = 405; return shell;}
        else if(shell->args[0] - '0' < 0 || shell->args[0] - '0' > 7)
        {shell->errn = 406; return shell;}

        else conf_ganancia(shell);
    }
    else if((shell->comando[0] == 'G') && (shell->comando[1] == 'T') && (shell->comando[2] == '0'))
    {
        if(shell->n_args > 0)
        {shell->errn = 405; return shell;}

        else get_timer0();
    }
    else if((shell->comando[0] == 'G') && (shell->comando[1] == 'T') && (shell->comando[2] == '2'))
    {
        if(shell->n_args > 0)
        {shell->errn = 405; return shell;}

        else get_timer2();
    }
    else if((shell->comando[0] == 'G') && (shell->comando[1] == 'P') && (shell->comando[2] == 'C'))
    {
        if(shell->n_args > 0)
        {shell->errn = 405; return shell;}

        // else get_PCA();
    }
    else if((shell->comando[0] == 'S') && (shell->comando[1] == 'C') && (shell->comando[2] == 'F'))
    {
        if(shell->n_args > 0)
        {shell->errn = 405; return shell;}

        else guardar_config(shell);
    }
    else if((shell->comando[0] == 'G') && (shell->comando[1] == 'C') && (shell->comando[2] == 'F'))
    {
        if(shell->n_args > 0)
        {shell->errn = 405; return shell;}

        else cargar_config(shell);
    }
    else if((shell->comando[0] == 'S') && (shell->comando[1] == 'H') && (shell->comando[2] == 'C'))
    {
        if(shell->n_args > 0)
        {shell->errn = 405; return shell;}

        else mostrar_config_flash();
    }

	else if((shell->comando[0] == 'S') && (shell->comando[1] == 'H') && (shell->comando[2] == 'A'))
    {
        if(shell->n_args > 0)
        {shell->errn = 405; return shell;}

        else mostrar_config_actual(shell);
    }

    else shell->errn = 404;

	return shell;

}


void reportar(struct shellstr *shell)
{
    switch(shell->errn)
    {   

        case 251: printf("\nACK 201: pin %c configurado en modo single_ended\n", shell->args[0]); break;
        case 252: printf("\nACK 202: pines %c y %c configurados en modo diferencial\n", shell->args[0], shell->args[0] + 1); break;
        case 253: printf("\nACK 253: ganancia configurada en 2^%c\n", shell->args[0]); break;
        case 404: printf("\nERROR 404: comando no encontrado\n"); break;
        case 405: printf("\nERROR 405: demasiados argumentos\n"); break;
        case 406: printf("\nERROR 406: alguno de los argumentos esta fuera de rango\n"); break;
        case 0: break; // para el caso donde se apreta enter solo
    }
}



// void printeartodo(struct shellstr *shell)
// {
//     int i;

//     printf("comando: ");
//     for(i = 0; i<TAM_COMANDO; i++)
//     {
//         printf("%c", shell->comando[i]);
//     }
//     printf("\n argumentos: ");
//     for(i = 0; i<shell->n_args; i++)
//     {
//         printf("%c", shell->args[i]);
//     }

//     printf("\nnumero de error: %hi\n", shell->errn);

// }