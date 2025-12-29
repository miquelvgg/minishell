/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epascual <epascual@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 18:49:05 by epascual          #+#    #+#             */
/*   Updated: 2025/12/29 18:49:12 by epascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Actualiza una env var
static void	update_env_var(t_data *shell, char *var_ass, int idx)
{
	free(shell->env[idx]);
	shell->env[idx] = ft_strdup(var_ass);
}

// Assigna una env var
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

// Crea el primer env que sera usado luego
char	**create_first_env(char **environ)
{
	char	**new_env;
	int		i;
	int		c;

	c = ft_stringlen(environ);
	new_env = (char **)ft_calloc(sizeof(char *), c + 1);
	if (!new_env)
		return (NULL);
	i = 0;
	while (environ[i])
	{
		new_env[i] = ft_strdup(environ[i]);
		if (!new_env[i])
		{
			while (--i >= 0)
				free(new_env[i]);
			free(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

// Crea un env sin la variable eliminada
char	**create_new_env(t_data *shell, int skip_idx, int count)
{
	char	**new_env;
	int		i;
	int		j;

	new_env = (char **)ft_calloc(sizeof(char *), count + 1);
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
		else
			free(shell->env[i]);
		i++;
	}
	new_env[j] = NULL;
	return (new_env);
}

// Sale de data
int	exit_var(t_data *data)
{
	int	i;

	if (!data->env)
		return (0);
	i = 0;
	while (data->env[i])
	{
		free(data->env[i]);
		i++;
	}
	free(data->env);
	data->env = NULL;
	return (0);
}
