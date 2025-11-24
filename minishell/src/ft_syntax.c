#include "minishell.h"

/*
int is_external_command(char *command) {
    char *path = getenv("PATH");
    char *dir = strtok(path, ":");

    while (dir != NULL) {
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);

        struct stat st;
        if (stat(full_path, &st) == 0 && st.st_mode & S_IXUSR) {
            return 1; // Existe y es ejecutable
        }
        dir = strtok(NULL, ":");
    }
    return 0;
}
*/


int get_com_built(char  *s)
{
	if (!ft_strcmp(s,"echo"))
		return(1);
	else if (!ft_strcmp(s,"cd"))
		return(1);
	else if (!ft_strcmp(s,"pwd"))
		return(1);
	else if (!ft_strcmp(s,"export"))
		return(1);
	else if (!ft_strcmp(s,"unset"))
		return(1);
	else if (!ft_strcmp(s,"evn"))
		return(1);
	else if (!ft_strcmp(s,"exit"))
		return(1);
#ifdef  M_EXTER_FUNC
	if (is_ext_comm_sim(s))
		return(1);
#endif
	return(0);
}


int	get_type(char *str, int *i)
{
	if (str[*i] == '|')
		return (T_PIPE);
	else if (str[*i] == '>')
	{
		if (str[*i + 1] == '>')
		{
			*i=*i+1;
			return (T_APPEND);
		}
		return (T_RDIR_OUT);
	}
	else if (str[*i] == '<')
	{
		if (str[*i + 1] == '<')
		{
			*i=*i+1;
			return (T_HERDOC);
		}
		return (T_RDIR_IN);
	}
	if (get_com_built(str))
		return (T_CMD);
	return (T_GENERAL);
}



void ft_analysis(char *token, t_token *mtk, int ix)
{
	int tp;
	int i;
	char *tmp;

	i = 0;

	
	while (token[i])
	{
		tp = get_type(token,&i);
		//printf("X(%d) type:(%d) data %s \n", mtk->index, mtk->type, mtk->data);
		i++;
	}
		mtk->index = ix;
		mtk->data = token;
		mtk->type = tp;
		//printf("X(%d) type:(%d) data %s \n", mtk->index, mtk->type, token[i]);	
		
		
		tmp = eval_expan(mtk->data);
		mtk->data = tmp;
		printf("%s\n",tmp);
		/*
		if (tmp)
		{
			free(mtk->data);
			mtk->data = tmp;
		}
			*/
		
}

int ft_syntax(t_data *dt, char ***tokens, int ntoken)
{
	int i;
	char **mtoken;
	
	i = 0;
	if (!tokens)
		return(0) ;
	mtoken = *tokens;
	dt->token = (t_token **) malloc(sizeof(t_token **) * (ntoken+1));
	if (!dt->token)
		return (-1);
	while ((mtoken[i] != NULL ))
	{
		dt->token[i] = malloc(sizeof(t_token));
		if (!dt->token[i])
		{
			while (--i)
				free(dt->token[i]);
			free(dt->token);
			return (-1);
		}
		ft_analysis(mtoken[i], dt->token[i],i);
		i++;	
	}
	dt->token[i] =NULL;
	return(0) ;
}
