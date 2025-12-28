#include "minishell.h"
void  print_env(t_data*data)
{

	char**environ= data->env;
	int i = 0;
	while(environ[i]) {
	  printf("%s\n", environ[i++]); // prints in form of "variable=value"
	}
}


int init() 
{
   	//unblock_signal(SIGINT);
	//unblock_signal(SIGQUIT);
	return(0);
}


//cc main.c  -lreadline 
/*
int init() {
    char *line;
    int salir=0;
    char cwd[1024];

	print_env();
	
//	signal(SIGINT, manejador_sigint);
	block_signal(SIGQUIT);
	block_signal(SIGINT);

    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        printf("Directorio actual: %s\n", cwd);
        return 1;
    }

  using_history();    
	while (!salir)	
	{
//	    line = readline(cwd);
		line = readline(READLINE_MSG);
	    if (line[0] == 'x')
	    {
	    	salir = 1;
	    }
	    add_history(line);
		free(line);    
	}
	 
    //printf("La línea ingresada es: %s\n", line);


    
   	unblock_signal(SIGINT);
	unblock_signal(SIGQUIT);
	
    return 0;
}
*/
