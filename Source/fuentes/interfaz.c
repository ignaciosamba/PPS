/**
 * @file interfaz.c
 * @author Sambataro, Ignacio; Mantovani, Luciano
 * @date 2015
 * @brief Funciones de interfaz de usuario e interpretacion de comandos
 * @details Este archivo contiene las funciones correspondientes a la obtencion y el procesado de los comandos
 * ingresados por el usuario
 */

#include "headers.h"
#include "conversor.h"
#include "flash.h"
#include "contador.h"
#include "interfaz.h"

/**
 * @brief Obtiene un comando
 * @details Se imprime un prompt, y luego de eso se espera que el usuario ingrese un comando con sus argumentos, 
 * si los hubiere. Tanto el comando como los argumentos son arreglos que pertenecen a la estructura shell, 
 * y son modificados y analizados por separado a nivel de caracter. Para la obtencion de ambos, se utiliza la 
 * funcion getchar()
 * 
 * @param shellstr la estructura de datos general. Utiliza los campos entrada, comando[], args[], y n_args
 * @return devuelve la misma estructura modificada.
 */
struct shellstr *obtener_entrada(struct shellstr *shell)
{
    char i = 0;
	printf("MML>"); // imprime el prompt

    //recibe el comando
    while((shell->entrada = getchar()) != ',')
    {
        if((shell->entrada == '\n') && (i == 0)){ shell->errn = 1000; return shell;}
        if(shell->entrada == '\n'){break;}

        if(i < TAM_COMANDO)  //la entrada debe ser menor al tamaño maximo de un comando
        {
            shell->comando[i] = shell->entrada;
            i++;
        }
        else shell->errn = 404;
    }

        // if(shell->comando[0] == '\n')
        //     {printf("comando0 es n\n"); shell->errn = 1000; return shell;}

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
    // if(shell->n_args > 7)

    if(shell->entrada != '\n')
    while (getchar() != '\n');

	return shell;
}

/**
 * @brief Analiza el comando y toma una accion segun el mismo
 * @details Esta funcion debe ser ejecutada luego de "obtener_entrada". Cuando se ingresa el comando y los 
 * argumentos si los hubiere, y se ejecuta esta funcion, se analiza el contenido del comando y se ejecuta
 * la funcion correspondiente, asegurandose antes de que no haya errores en los argumentos, siempre que los
 * haya
 * 
 * @param shellstr la estructura de datos general. Utiliza los campos comando[], args[], n_args y errn
 * @return devuelve la misma estructura modificada.
 */
struct shellstr *analizar(struct shellstr *shell)
{
        // printf("lalalalalal\n");
    if((shell->comando[0] == 'S') && (shell->comando[1] == 'T'))
    {
        shell->errn = 254;
        shell->stop_conf = 0;
    }


    else if((shell->comando[0] == 'S') && (shell->comando[1] == 'S') && (shell->comando[2] == 'E'))
    {
        if(shell->n_args > 7)
        {shell->errn = 405; return shell;}
        else if(shell->args[1] != ',' )
        {shell->errn = 406; return shell;}
        else if(shell->args[0] - '0' < 0 || shell->args[0] - '0' > 7)
        {shell->errn = 406; return shell;}

        cargar_buffer_single(shell);
    }
    else if((shell->comando[0] == 'S') && (shell->comando[1] == 'D') && (shell->comando[2] == 'I'))
    {
        if(shell->n_args > 6 || shell->n_args % 2 != 0)
        {shell->errn = 405; return shell;}
        else if(shell->args[0] - '0' < 0 || shell->args[0] - '0' > 6)
        {shell->errn = 406; return shell;}

        cargar_buffer_dif(shell);
    }
    else if((shell->comando[0] == 'G') && (shell->comando[1] == 'S') && (shell->comando[2] == 'E'))
    {
        if(shell->n_args > 7)
        {shell->errn = 405; return shell;}
        else if(shell->args[1] != ',' )
        {shell->errn = 406; return shell;}
        else if(shell->args[0] - '0' < 0 || shell->args[0] - '0' > 7)
        {shell->errn = 406; return shell;}

        get_single_ended(shell);
    }
    else if((shell->comando[0] == 'G') && (shell->comando[1] == 'D') && (shell->comando[2] == 'I'))
    {
        if(shell->n_args > 6 || shell->n_args % 2 != 0)
        {shell->errn = 405; return shell;}
        else if(shell->args[0] - '0' < 0 || shell->args[0] - '0' > 6)
        {shell->errn = 406; return shell;}

        get_differential(shell);
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

    else if((shell->comando[0] == 'G') && (shell->comando[1] == 'R') && (shell->comando[2] == 'P'))
    {
        if(shell->n_args > 0)
        {shell->errn = 405; return shell;}

        else contar_RPM();
    }

    else shell->errn = 404;

    return shell;

}

/**
 * @brief Reporte de errores
 * @details Esta funcion analiza el estado de la variable errn, que esta dentro de la estructura shell, y 
 * segun ese valor imprime un mensaje en la pantalla, ya sea por un error o un acknowledge
 * 
 * @param shellstr la estructura general del programa, usa el parametro errn
 */
void reportar(struct shellstr *shell)
{
    switch(shell->errn)
    {   
        case 251: printf("\nACK 251: pin %c configurado en modo single_ended\n", shell->args[0]); break;
        case 252: printf("\nACK 252: pines %c y %c configurados en modo diferencial\n", shell->args[0], shell->args[0] + 1); break;
        case 253: printf("\nACK 253: ganancia configurada en 2^%c\n", shell->args[0]); break;
        case 254: printf("\nACK 254: inicio de conversion y envio de datos. para volver al menu presione 's'"); break;
        case 404: printf("\nERROR 404: comando no encontrado\n"); break;
        case 405: printf("\nERROR 405: demasiados argumentos\n"); break;
        case 406: printf("\nERROR 406: alguno de los argumentos esta fuera de rango\n"); break;
        case 0: break; // para el caso donde se apreta enter solo
        default: break;
    }
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
//         printf("%c, ", shell->args[i]);
//     }
//     printf("\n");

//     printf("\n numero de argumentos: %d\n", (int)shell->n_args);
//     // printf("buffer_adc: \n");
//     // for(i = 0; i<TAM_SINGLE; i++)
//     // {
//     //     printf("buffer_adc[%d] = %c\n", shell->buffer_adc[i], i);
//     // }
//     printf("buffer_adc_count: \n");
//     for(i = 0; i<TAM_SINGLE; i++)
//     {
//         printf("buffer_adc_count[%d] = %c\n", i, shell->buffer_adc_count[i]);
//     }


//     printf("\nnumero de error: %hi\n", shell->errn);

// }