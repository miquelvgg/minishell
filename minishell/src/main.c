#include "minishell.h"

//Imprime acciones
void	print_actions(t_data *d)
{
	int		i;
	int		j;
	t_action *act;

	if (!d) {
		printf("print_actions: data es NULL\n");
		return;
	}
	if (!d->actions || d->n_actions <= 0) {
		printf("print_actions: no hay acciones\n");
		return;
	}
	
	printf("===== ACCIONES (total: %d) =====\n", d->n_actions);
	i = 0;
	while (i < d->n_actions)
	{
		act = &d->actions[i];
		printf("---- Acción %d ----\n", i);
		printf("index   : %d\n", act->index);
		/* argv */
		printf("argv    : ");
		if (!act->argv)
			printf("(null)\n");
		else 
		{
			j = 0;
			while (act->argv[j])
			{
				printf("[%d] \"%s\"  ", j, act->argv[j]);
				j++;
      		}
		if (j == 0)
			printf("(vacío)");
		printf("\n");
	}
    /* redirecciones */
	printf("infile  : %s\n", act->infile ? act->infile : "(null)");
	printf("outfile : %s\n", act->outfile ? act->outfile : "(null)");
	printf("append  : %d\n", act->append);

	/* fds (si los usas) */
	printf("fd_in   : %d\n", act->fd_in);
	printf("fd_out  : %d\n", act->fd_out);

	printf("--------------------\n");
	i++;
	}
	printf("===== FIN ACCIONES =====\n");
}

//Libera el data struct
void free_data_struc(t_data *dt)
{
	int i;

	if (!dt->token)
		return;

	i = 0;
	while (dt->token[i] != NULL)
	{
		if (dt->token[i]->data) 
		{
			free(dt->token[i]->data);
			dt->token[i]->data = NULL;
		}
		if (dt->token[i]) 
		{
			free(dt->token[i]);
			dt->token[i] = NULL;
		}
		i++;
	}
	if (dt->token != NULL)
		free(dt->token);
}

//Imprime los tokens
void paint_token(t_data	*data)
{
	int		i;
	t_token **mtoken;
	
	i = 0;
	if (!data->token)
    	return;
	mtoken = data->token;
	
	while ((mtoken[i] != NULL))
	{
		printf("(%d) %s \n", i, mtoken[i]->data);
		i++;
	}
}

/*
void mpaint_token(char ***tokens)
{
	int i= 0 ;
	char **p;

	p = *tokens;
	while (p[i])
	{
		printf("%s \n",p[i]);
		i++;
	}
}
*/


//Nucleo del proyecto
int mshell(t_data	*data)
{
	int		salir;
	char	*line;
	char	**atoken;
	int		ntoken;
	int		rt;
	
	rt = 0;
	ntoken = 0;
	atoken = NULL;
	data->signal_status = 0;
	salir = 0;
	using_history();//initialize history 
	setup_signals();
	while (!salir)
	{
		g_signal = 0; 
		line = readline(READLINE_MSG);
		if (g_signal == (int)SIGQUIT)
		{	
			write(1, "1exit\n", 6);
			if (line != NULL)
				free(line);
			
			break;
		}
		else if (!line )
		{
			write(1, "2exit\n", 6);
			break;
		}
		else 
		{
			ntoken =shell_tokenize(line, &atoken);
			if (ntoken > 0)
			{
					//mpaint_token(&atoken);
					rt = ft_syntax(data, &atoken, ntoken);
					if (rt)
					{
						free_token(&atoken, ntoken); // ell texto de la estructura es un apuntador a array inicial de tokens
						free_data_struc(data); // free space malloc
						free(line);
						return(1);
					}
					//paint_token(data);
					rt = ft_actions(data);
//					paint_token(data);
//					print_actions(data );//DEBUGEAO
					if (rt)
					{
						free_actions(data);
						free_token(&atoken, ntoken); // ell texto de la estructura es un apuntador a array inicial de tokens
						free_data_struc(data); // free space malloc
						free(line);
						return(1);
					}

					rt = ((atoken)&&(ntoken)&&(atoken[ntoken-1][0] == '|'));
					free_token(&atoken, ntoken); // ell texto de la estructura es un apuntador a array inicial de tokens
					if (!rt)
					{
						exactions(data);
					}
					else 
					{
						//perror("Error : pipe");
						printf("Error : pipe\n");

					}
					free_actions(data);
					free_data_struc(data); // free space malloc
					
				}
			if (*line) 
				add_history(line);
			}
		if (line)
			free(line);
	}
	return(0);
}

//Comprueba los estandares
int ft_control(int argc, char **argv)
{

  (void)argv;
  if (argc != 1)
    return (1);
  if (!isatty(STDIN_FILENO)) {
    fprintf(stderr,
            "Error: No se permite redireccionar la entrada estándar.\n");
    return (2);
  }

  if (!isatty(STDOUT_FILENO)) {
    fprintf(stderr, "Error: No se permite redireccionar la salida estándar.\n");
    return (3);
  }
  return (0);
}

//Inicia data
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

/* definir errores de salida */
//Main, inicia env
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

	data.env = create_first_env(env, &data);
	//print_env(&data);//DEBUGEAO
	//ft_memset(&data, 0, sizeof(t_data));
	if (!res)
		res	= mshell(&data);
	exit_var(&data);
	
  //	exit_shelly(&data);
  return (0);
}