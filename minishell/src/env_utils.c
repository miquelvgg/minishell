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

//Cuando corres la shell sin environment necesita minimo estos env
void	init_minimal_env(t_data*shell)
{
	shell->env = (char**)malloc(sizeof(char*) * 2);
	set_env_var(shell, "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
	set_env_var(shell, "PWD=/bin");
}

//Actualiza una env var
static void	update_env_var(t_data *shell, char *var_assignment, int idx)
{
	free(shell->env[idx]);
	shell->env[idx] = (char *)malloc(ft_strlen(var_assignment) + 1);
	if (!shell->env[idx])
		return ;
	ft_strlcpy(shell->env[idx], var_assignment, ft_strlen(var_assignment) + 1);
}

//Assigna una env var
void	set_env_var(t_data *shell, char *var_assignment)
{
	char	*equal_sign;
	int		name_len;
	int		idx;

	equal_sign = ft_strrchr(var_assignment, '=');
	if (!equal_sign)
		return ;
	name_len = equal_sign - var_assignment;
	idx = find_env_var(shell->env, var_assignment, name_len);
	if (idx >= 0)
		update_env_var(shell, var_assignment, idx);
	else
		add_env_var(shell, var_assignment);
}

//Crea el primer env que sera usado luego
char	**create_first_env(char**environ, t_data*shell)
{
	char	**new_env;
	int		i;
	int		c;

	c = ft_stringlen(environ);
	if (environ[0] == NULL)
		init_minimal_env(shell);
	new_env = (char **)malloc(sizeof(char *) * c);
	if (!new_env)
		return (NULL);
	i = 0;
	while (environ[i])
	{
		new_env[i] = environ[i];
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

//Crea un env sin la variable eliminada
char	**create_new_env(t_data *shell, int skip_idx, int count)
{
	char	**new_env;
	int		i;
	int		j;

	new_env = (char **)malloc(sizeof(char *) * count);
	if (!new_env)
		return (NULL);
	i = 0;
	j = 0;
	while (shell->env[i])
	{
		if (i != skip_idx)
		{
			new_env[j] = shell->env[i];
			j++;
		}
	//	else
	//		free(shell->env[i]);
		i++;
	}
	new_env[j] = NULL;
	return (new_env);
}

//Elimina una env var
void	unset_env_var(t_data *shell, char *var_name)
{
	int		idx;
	int		count;
	char	**new_env;
	size_t	name_len;

	name_len = ft_strlen(var_name);
	idx = find_env_var(shell->env, var_name, name_len);
	if (idx < 0)
		return ;
	count = 0;
	while (shell->env[count])
		count++;
	new_env = create_new_env(shell, idx, count);
	if (!new_env)
		return ;
	free(shell->env);
	shell->env = new_env;
}
