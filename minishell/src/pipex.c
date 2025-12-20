/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epascual <epascual@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:32:53 by epascual          #+#    #+#             */
/*   Updated: 2025/12/20 11:54:01 by epascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;

	i = -1;
	allpath = ft_split(my_getenv("PATH", env), ':');
	if (!allpath)
		exit(2);
	while (allpath[++i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, cmd);
		if (access(exec, F_OK | X_OK) == 0)
		{
			free(allpath);
			return (exec);
		}
		free(exec);
	}
	free(allpath);
	exec = ft_strdup(cmd);
	return (exec);
}
