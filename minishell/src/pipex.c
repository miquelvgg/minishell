/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epascual <epascual@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:32:53 by epascual          #+#    #+#             */
/*   Updated: 2025/11/29 15:26:44 by epascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;
	char	**s_cmd;

	i = -1;
	allpath = ft_split(my_getenv("PATH", env), ':');
	if (!allpath)
		exit(2);
	s_cmd = ft_split(cmd, ' ');
	while (allpath[++i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, s_cmd[0]);
		//free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			//ft_free_pointstring(s_cmd);
			return (exec);
		}
		//free(exec);
	}
	//doblefree(s_cmd, allpath);
	return (cmd);
}

//Ejecuta el comando
void	exec(char *cmd, char **env)
{
	char	**s_cmd;
	char	*path;
	int		excode;

	s_cmd = ft_split(cmd, ' ');
	path = get_path(s_cmd[0], env);
	excode = execve(path, s_cmd, env);
	if (excode != 0)
	{
		ft_free_pointstring(s_cmd);
		exit(excode);
	}
}

//Crea el pipe y los hijos
void	do_pipe(char *cmd, char **env)
{
	t_pid	pid;
	int		p_fd[2];

	if (pipe(p_fd) == -1)
		exit(-2);
	pid = fork();
	if (pid == -1)
		exit(-2);
	if (!pid)
	{
		close(p_fd[0]);
		dup2(p_fd[1], 1);
		exec(cmd, env);//sustituir con execute
	}
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], 0);
		waitpid(pid, NULL, 0);
	}
}

//Abre archivos y llama las pipes
void	pipex(int input, int argc, char **argv, char**envp)
{
	int	output;
	int	i;

	i = 2;
	input = open(argv[1], 0, 0777);
	if (input < 0)
	{
		//ft_printfd(2, "no such file or directory: %s\n", argv[1]);
		perror("no such file or directory");
		close(input);
		exit(errno);
	}
	output = open(argv[argc - 1], 577, 0777);
	if (output < 0)
	{
	close(input);
	close(output);
		exit(-1);
	}
	dup2(input, 0);
	while (i < argc - 2)
	{
		do_pipe(argv[i], envp);
		i++;
	}
	dup2(output, 1);
	exec(argv[argc - 2], envp);
}
