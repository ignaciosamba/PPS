#include "headers_logic.h"
#include "interfaz.h"

char correr_shell(struct shellstr *shell)
{

	printf("MML>"); // prints out the prompt
	char *shell->entrada;
    fgets(shell->entrada, MAXSIZE, stdin);
            
    if (shell->entrada == NULL)
    {
        printf("\n");
        return 0;    
    }
    // add_history(shell->entrada);


	if (strlen(shell->entrada) > 1)
	{
		shell = parsear_entrada(shell);													
		shell = analizar(shell); 

		// if(shell->report != 0)
		// 	report(shell->report);
		// shell->report = 0;

		restart(shell);
	}

	return 0;
}

void restart(struct shellstr *shell)
{       
    int i;
    for (i = 0; i<shell->n_args;i++)
        shell->args[i] = NULL;
}

struct shellstr *parsear_entrada(struct shellstr *shell)
{

	char *buffer;
    char *temp1;
    char *temp2 = NULL;
    int i = 0;
    
    shell->n_args = 1; //initialized to 1 by default, it updates later if there are any arguments

    //and now we parse  
    shell->comando = strtok(shell->entrada, ":");
    strip(shell->comando);

    //the rest of the string remaining in buffer are the arguments. so we continue parsing
    while ((buffer = strtok(NULL, ",")) != NULL)
    {	
        shell->args[i] = buffer;
        i++;
        if(i == 4)
        {
        	/*no puede haber mas de 4 argumentos*/
        	return shell;
        }
    }
    shell->n_args = i;


	return shell;
}

struct shellstr *analizar(struct shellstr *shell)
{

	if(!strcmp(shell->comando,"SAE"))
    {
    	printf("guardando y saliendo\n");
    	return shell;
    }
	else if(!strcmp(shell->comando,"load")){ shell = printf("comando\n");; return shell;}

	else printf("comando '%s' not found\n",shell->comando); //TODO: ERRORES!!!

	return shell;

}