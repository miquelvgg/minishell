#include "minishell.h"

void paint_token(char ***token, int nt)
{
	int i;
	char **mtoken;

	i = 0;
	if (!token)
		return ;
	mtoken = *token;

	while ((mtoken[i] != NULL ) &&(i < nt))
	{
		printf("(%d) %s \n",i,mtoken[i]);
		i++;
	}
}


void free_token(char ***token, int nt)
{
	int i;
	char **mtoken;
	
	i = 0;
	if (!token)
		return ;
	mtoken = *token;

	while ((mtoken[i] != NULL ) &&(i < nt))
	{
		free(mtoken[i]);
		i++;
	}
	free(mtoken);
	
}


int mshell(t_data	*data)
{
	int salir;
	char *line;
	//int t;
	char **atoken;
	int ntoken;

	ntoken = 0;
	atoken = NULL;
	//(void)data;
	data->signal_status = 0;
	salir = 0;
	block_signal(SIGQUIT);
	block_signal(SIGINT);
  	
	using_history();     //initialize history 
	while (!salir)	
	{
		line = readline(READLINE_MSG);
	    if (line[0] == 'x')
	    {
	    	salir = 1;
	    }
		else 
		{
			//t = count_tokens_and_validate(line) ;
			//printf(" %d\n",t);
			ntoken =shell_tokenize(line, &atoken);
			paint_token(&atoken, ntoken);
			free_token(&atoken, ntoken);
			data->token->data=line;
			execute(data);
		}

		 if (*line) 
			add_history(line);
	    	
		free(line);    
	}
   	unblock_signal(SIGINT);
	unblock_signal(SIGQUIT);
	return(0);
}

int ft_control(int argc, char **argv)
{

	(void)argv;
	if (argc != 1)
		return(1);
	 if (!isatty(STDIN_FILENO)) {
        fprintf(stderr, "Error: No se permite redireccionar la entrada estándar.\n");
        return (2);
    }

    if (!isatty(STDOUT_FILENO)) {
        fprintf(stderr, "Error: No se permite redireccionar la salida estándar.\n");
        return (3);
    }
	return (0);
}

int  init_var(t_data	*data)
{
	t_token *new_token = malloc(sizeof(t_token));
	if (!new_token)
		return(1);
	data->signal_status= 0;
	data->token	= new_token;
	data->user_input =NULL; 	/* */
	data->env=NULL;			/* */
	data->working_dir=NULL;	/* */
	data->old_working_dir=NULL; /* */

	return(0);
}

int  exit_var(t_data	*data)
{
	if (data->token)
		free(data->token);

	return(0);
}


/* definir errores de salida */

int main(int argc, char **argv, char **env)
{
	t_data	data;
	int		res;
	
	if (ft_control(argc,argv))
		return (1);
	

    if (!isatty(STDOUT_FILENO)) {
        fprintf(stderr, "Error: No se permite redireccionar la salida estándar.\n");
        return 1;
    }

	// guardar valores de 	extern char **environ;
	
	res = init_var(&data);
	data.env = env;
	//ft_memset(&data, 0, sizeof(t_data));
	if (!res)
		res	= mshell(&data);
	exit_var(&data);

//	exit_shelly(&data);
	return (0);
}
