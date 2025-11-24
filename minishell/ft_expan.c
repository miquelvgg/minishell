#include "minishell.h"


//Encuentra una variable en env por el nombre
int	find_env_var(char **env, const char *name, int name_len)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, name_len) == 0
			&& env[i][name_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

/* Mira si hay expan.*/
/* crea  nuevo expan.(si puede) */
/* crea nuevo token y libera token de readline */
void eval_expan(char *token, int xp)
{

}