#include "minishell.h"

//Copia variables de entorno a nuevo array
static void	copy_existing_vars(char **new_envp, char **old_envp, int count)
{
	int	idx;

	idx = 0;
	while (idx < count)
	{
		new_envp[idx] = old_envp[idx];
		idx++;
	}
}

//Crea y copia nuevas variables string
static char	*create_var_copy(char *var_assignment)
{
	char	*new_var;
	size_t	var_len;

	var_len = ft_strlen(var_assignment);
	new_var = (char *)malloc(var_len +1);
	if (!new_var)
		return (NULL);
	ft_strlcpy(new_var, var_assignment, var_len + 1);
	return (new_var);
}

//Anade nueva variable al env array
void	add_env_var(t_data *shell, char *var_assignment)
{
	int		count;
	char	**new_envp;

	count = ft_stringlen(shell->env);
	new_envp = (char **)malloc(sizeof(char *) * (count + 2));
	if (!new_envp)
		return ;
	copy_existing_vars(new_envp, shell->env, count);
	new_envp[count] = create_var_copy(var_assignment);
	if (!new_envp[count])
	{
		free(new_envp);
		return ;
	}
	new_envp[count + 1] = NULL;
	free(shell->env);
	shell->env = new_envp;
}
