/**
 * @file interfaz.c
 * @author Sambataro, Ignacio; Mantovani, Luciano
 * @date 2015
 * @brief Funciones de interfaz de usuario e interpretacion de comandos
 * @details Este archivo contiene las funciones correspondientes a la obtencion y el procesado de los comandos
 * ingresados por el usuario
 */

#include "headers.h"
#include "sensorCE/funciones_sensor.h"
#include "conversor.h"
#include "contador.h"
#include "interfaz.h"
#include "configurador.h"

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
	// printf("0MML>"); // imprime el prompt
    shell->errn = 0;

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

        return shell;
    }


    else if((shell->comando[0] == 'S') && (shell->comando[1] == 'S') && (shell->comando[2] == 'E'))
    {
        if(shell->n_args > 5)
        {shell->errn = 405; return shell;}
        else if(shell->args[1] != ',' && shell->n_args < 2 || shell->n_args == 0)
        {shell->errn = 407; return shell;}
        else if(shell->args[1] != ',' && shell->n_args >= 2)
        {shell->errn = 408; return shell;}
        else if(shell->args[1] == ',' && shell->n_args < 3)
        {shell->errn = 408; return shell;}
        else if(shell->args[0] - '0' < 0 || shell->args[0] - '0' > 7)
        {shell->errn = 406; return shell;}
        else if( shell->n_args > 2 && (shell->args[2] - '0' < 0 || shell->args[2] - '0' > 9))
        {shell->errn = 406; return shell;}
        else if( shell->n_args > 3 && (shell->args[3] - '0' < 0 || shell->args[3] - '0' > 9))
        {shell->errn = 406; return shell;}
        else if( shell->n_args > 4 && (shell->args[4] - '0' < 0 || shell->args[4] - '0' > 9))
        {shell->errn = 406; return shell;}
        else if( shell->n_args > 4 && ((unsigned)(atoi(shell->args + 2)) > 255))
        {shell->errn = 406; return shell;}

        cargar_buffer_single(shell);

        return shell;
    }
    else if((shell->comando[0] == 'S') && (shell->comando[1] == 'D') && (shell->comando[2] == 'I'))
    {
        if(shell->n_args > 5)
        {shell->errn = 405; return shell;}
        else if(shell->args[1] != ',' && shell->n_args < 2)
        {shell->errn = 407; return shell;}
        else if(shell->args[1] != ',' && shell->n_args >= 2)
        {shell->errn = 408; return shell;}
        else if(shell->args[1] == ',' && shell->n_args < 3)
        {shell->errn = 408; return shell;}
        else if(shell->args[0] - '0' < 0 || shell->args[0] - '0' > 6 || (shell->args[0] & 1))
        {shell->errn = 406; return shell;}
        else if( shell->n_args > 2 && (shell->args[2] - '0' < 0 || shell->args[2] - '0' > 9))
        {shell->errn = 406; return shell;}
        else if( shell->n_args > 3 && (shell->args[3] - '0' < 0 || shell->args[3] - '0' > 9))
        {shell->errn = 406; return shell;}
        else if( shell->n_args > 4 && (shell->args[4] - '0' < 0 || shell->args[4] - '0' > 9))
        {shell->errn = 406; return shell;}
        else if( shell->n_args > 4 && ((unsigned)(atoi(shell->args + 2)) > 255))
        {shell->errn = 406; return shell;}

        cargar_buffer_dif(shell);

        return shell;
    }
    else if((shell->comando[0] == 'G') && (shell->comando[1] == 'S') && (shell->comando[2] == 'E'))
    {
        if(shell->n_args > 1)
        {shell->errn = 405; return shell;}
        else if(shell->args[0] - '0' < 0 || shell->args[0] - '0' > 7)
        {shell->errn = 406; return shell;}

        get_single_ended(shell);

        return shell;
    }
    else if((shell->comando[0] == 'G') && (shell->comando[1] == 'D') && (shell->comando[2] == 'I'))
    {
        if(shell->n_args > 6)
        {shell->errn = 405; return shell;}
        
        else if(shell->args[0] - '0' < 0 || shell->args[0] - '0' > 6)
        {shell->errn = 406; return shell;}

        get_differential(shell);

        return shell;
    }
    else if((shell->comando[0] == 'S') && (shell->comando[1] == 'G') && (shell->comando[2] == 'A'))
    {
        if(shell->n_args > 1)
        {shell->errn = 405; return shell;}
        else if(shell->args[0] - '0' < 0 || shell->args[0] - '0' > 7)
        {shell->errn = 406; return shell;}

        else conf_ganancia(shell);

        return shell;
    }
    else if((shell->comando[0] == 'G') && (shell->comando[1] == 'T') && (shell->comando[2] == '0'))
    {
        if(shell->n_args > 0)
        {shell->errn = 405; return shell;}

        else get_timer0();

        return shell;
    }
    else if((shell->comando[0] == 'G') && (shell->comando[1] == 'T') && (shell->comando[2] == '2'))
    {
        if(shell->n_args > 0)
        {shell->errn = 405; return shell;}

        else get_timer2();

        return shell;
    }
    // else if((shell->comando[0] == 'G') && (shell->comando[1] == 'P') && (shell->comando[2] == 'C'))
    // {
    //     if(shell->n_args > 0)
    //     {shell->errn = 405; return shell;}

    //     // else get_PCA();
    // }
    else if((shell->comando[0] == 'S') && (shell->comando[1] == 'H') && (shell->comando[2] == 'A'))
    {
        if(shell->n_args > 0)
        {shell->errn = 405; return shell;}

        else mostrar_config_actual(shell);

        return shell;
    }

    else if((shell->comando[0] == 'G') && (shell->comando[1] == 'R') && (shell->comando[2] == 'P'))
    {
        if(shell->n_args > 0)
        {shell->errn = 405; return shell;}

        else RPM_instantaneo();

        return shell;
    }

    else if((shell->comando[0] == 'P') && (shell->comando[1] == 'W') && (shell->comando[2] == 'M'))
    {
        if(shell->n_args > 0)
        {shell->errn = 405; return shell;}

        else arrancar_motor();
        shell->errn = 301;

        return shell;
    }

    else if((shell->comando[0] == 'N') && (shell->comando[1] == 'T') && (shell->comando[2] == 'P'))
    {
        if(shell->n_args > 0)
        {shell->errn = 405; return shell;}

        else apagar_motor();
        shell->errn = 302;

        return shell;
    }
    else if((shell->comando[0] == 'S') && (shell->comando[1] == 'L') && (shell->comando[2] == 'P'))
    {
        if(shell->n_args > 0)
        {shell->errn = 405; return shell;}

        else habilitar_modo_bajo_consumo();

        return shell;
    }
    else if((shell->comando[0] == 'E') && (shell->comando[1] == 'S') && (shell->comando[2] == 'C'))
    {
        if(shell->n_args > 0)
        {shell->errn = 405; return shell;}

        else resetear_motor();

        return shell;
    }
    else if((shell->comando[0] == 'C') && (shell->comando[1] == 'N') && (shell->comando[2] == 'F'))
    {
        if(shell->n_args > 0)
        {shell->errn = 405; return shell;}

        else configurar_motor();

        return shell;
    }
    else if(shell->comando[0] == 'p')
    {
        refresh_watchDog();
        shell->errn = 501; // stillOn successful
        return shell;
    }
    else if (shell->comando[0] == 'e')
    {
        shell->errn = 502;
        return shell;
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
        case 251: printf("%05d", 251); break; // pin configurado en modo single-ended
        case 252: printf("%05d", 252); break; // pin configurado en modo diferencial
        case 253: printf("%05d", 253); break; // ganancia configurada
        case 254: printf("%05d", 254); break; // comienza la conversion continua
        case 301: printf("%05d", 301); break; // motor arranco
        case 302: printf("%05d", 302); break; // motor paro
        case 404: printf("%05d", 404); break; // comando no encontrado
        case 405: printf("%05d", 405); break; // demasiados argumentos
        case 406: printf("%05d", 406); break; // argumento(s) fuera de rango
        case 407: printf("%05d", 407); break; // error de sintaxis
        case 408: printf("%05d", 408); break; // error de sintaxis
        case 500: printf("%05d", 500); break; // stop succesful
        case 501: printf("%05d", 501); break; // stillOn successul
        case 502: printf("%05d", 502); break; // Inactive Server Stop
        case 503: printf("%05d", 503); break; // Send petition
        case 0: break; // para el caso donde se apreta enter solo
        default: break;
    }

    return;
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