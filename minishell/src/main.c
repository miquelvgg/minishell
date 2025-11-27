#include "minishell.h"


void free_data_struc(t_data *dt)
{
	int i;

	i = 0;
	while (dt->token[i]!= NULL)
	{
		free(dt->token[i]);
		i++;
	}
	if (dt->token != NULL)
		free(dt->token);
} 

void paint_token(char ***token, int nt)
{
	int i;
	char **mtoken;

	i = 0;
	if ((!token) || (!*token))
		return ;
	mtoken = *token;

	while ((mtoken[i] != NULL ) &&(i < nt))
	{
		printf("(%d) %s \n",i,mtoken[i]);
		i++;
	}
}

int mshell(t_data	*data)
{
	int salir;
	char *line;
	//int t;
	char **atoken;
	int ntoken;
	int rt;

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
			//t = count_tokens_and_validate(line) ;
			//printf(" %d\n",t);
			
			if (line[0]=='x')
				salir =1;
			ntoken =shell_tokenize(line, &atoken);
			if (ntoken > 0)
			{
				rt = ft_syntax(data, &atoken, ntoken);
//				if (!rt)
//					paint_token(data);
				//data->token->data = line;
				selexecute(data);
				free_token(&atoken, ntoken); // ell texto de la estructura es un apuntador a array inicial de tokens
				free_data_struc(data); // free space malloc
				
			}
			//printf("%s\n",data->token[0]->data);
			
			//paint_token(&atoken, ntoken);
			//free_token(&atoken, ntoken);
			//data->token->data=line;
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
/*	tn_token *new_token = malloc(sizeof(tn_token));
	if (!new_token)
		return(1);*/
	data->signal_status= 0;
	data->token	= NULL;	//&new_token;
	data->user_input =NULL;
	data->env=NULL;			
	data->working_dir=NULL;	
	data->old_working_dir=NULL; 
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
	if (!env || !*env)
		data.env = create_first_env(env, &data);
	data.env =env;
	//ft_memset(&data, 0, sizeof(t_data));
	if (!res)
		res	= mshell(&data);
//	exit_var(&data);

//	exit_shelly(&data);
	return (0);
}
