/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exacti_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epascual <epascual@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 13:35:23 by epascual          #+#    #+#             */
/*   Updated: 2025/12/29 13:35:24 by epascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Comprueba existencia archivo
void	existcmd(char *cmd)
{
	if (cmd == NULL || access(cmd, F_OK) != 0)
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd("\n", 2);
		exit(127);
	}
}

//Comprueba archivo ejecutable
void	is_exec(char *cmd)
{
	if (access(cmd, F_OK | X_OK) != 0)
	{
		ft_putstr_fd("Permission denied\n", 2);
		exit(126);
	}
}

//Comprueba ejecutable no sea directorio
void	is_dir(char *cmd)
{
	struct stat	pathstat;

	if (stat(cmd, &pathstat) == 0)
	{
		if (S_ISDIR(pathstat.st_mode))
		{
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(" is a directory\n", 2);
			exit(126);
		}
	}
}

//Error de no path
void	ft_nopath(void)
{
	ft_putstr_fd("PATH env not set\n", 2);
	exit(127);
}

//Obtiene una variable de environment
char	*my_getenv(char *name, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	if (!env || !env[0])
		return (NULL);
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (ft_strcmp(sub, name) == 0)
		{
			free(sub);
			return (env[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}
