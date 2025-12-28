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
