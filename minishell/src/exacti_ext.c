/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exacti_ext.c                                      :+:      :+:    :+:    */
/*                                                    +:+ +:+         +:+     */
/*   By: epascual <epascual@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 13:35:23 by epascual          #+#    #+#             */
/*   Updated: 2025/12/29 13:35:24 by epascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Libera arrays de strings
void	ft_free_pointstring(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

//strjoin que no libera memoria
char	*ft_nfstrjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	res = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		res[i++] = s2[j++];
	res[i] = '\0';
	return (res);
}

//Obtiene el path
char	*get_path(char *cmd, char **env)
{
	int		i;
	char	**paths;
	char	*path_part;
	char	*exec;

	paths = ft_split(my_getenv("PATH", env), ':');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[i++])
	{
		path_part = ft_nfstrjoin(paths[i], "/");
		exec = ft_nfstrjoin(path_part, cmd);
		free(path_part);
		if (access(exec, F_OK) == 0)
		{
			is_dir(exec);
			is_exec(exec);
			return (ft_free_pointstring(paths), exec);
		}
		free(exec);
	}
	return (ft_free_pointstring(paths), NULL);
}

int	redir_in_parent(t_action *act)
{
	int	fd;

	if (act->heredoc && act->heredoc_fd != -1)
	{
		dup2(act->heredoc_fd, STDIN_FILENO);
		close(act->heredoc_fd);
		act->heredoc_fd = -1;
		return (0);
	}
	if (!act->infile)
		return (0);
	fd = open(act->infile, O_RDONLY);
	if (fd < 0)
		return (1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	redir_out_parent(t_action *act)
{
	int	fd;
	int	flags;

	if (!act->outfile)
		return (0);
	flags = O_CREAT | O_WRONLY;
	if (act->append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(act->outfile, flags, 0644);
	if (fd < 0)
		return (1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}
