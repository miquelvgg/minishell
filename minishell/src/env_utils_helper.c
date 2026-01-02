/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epascual <epascual@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 12:17:00 by epascual          #+#    #+#             */
/*   Updated: 2026/01/02 19:47:59 by epascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	new_var = (char *)ft_calloc(var_len +1, 1);
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
	new_envp = (char **)ft_calloc(sizeof(char *), (count + 2));
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

// Elimina una env var
void	unset_env_var(t_data *shell, char *var_name)
{
	int		idx;
	int		count;
	char	**new_env;
	size_t	name_len;

	if (!shell->env)
		return ;
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

// Encuentra una variable en env por el nombre
int	find_env_var(char **env, const char *name, int name_len)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, name_len) == 0 && env[i][name_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}
