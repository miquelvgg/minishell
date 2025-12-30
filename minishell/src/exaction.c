#include "minishell.h"
/*
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

//Error de no path
void	ft_nopath(void)
{
	ft_putstr_fd("PATH env not set\n", 2);
	exit(127);
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

//Ejecuta ruta directa
void	directexec(t_action act, t_data*minishell)
{
	int	excode;

	excode = 0;
	is_dir(act.argv[0]);
	existcmd(act.argv[0]);
	is_exec(act.argv[0]);
	excode = execve(act.argv[0], act.argv, minishell->env);
	exit(excode);
}

//executa un pipecomand
void	executep(t_action act, t_data*minishell)
{
	char	*path;
	int		excode;

	excode = 0;
	if (is_builtin(act.argv[0]))
	{
		execute_builtin(act.argv, minishell);
		exit(minishell->xstatus);
	}
	else
	{
		if (ft_strchr(act.argv[0], '/'))
			directexec(act, minishell);
		path = get_path(act.argv[0], minishell->env);
		if (!path)
			existcmd(act.argv[0]);
		excode = execve(path, act.argv, minishell->env);
		if (excode == -1)
		{
			printf("Fallo execve\n");
			free(path);
			exit(127);
		}
	}
}


//Ejecuta pipe(ultimo)
void	exactionp(t_action act, t_data*data)
{
	preparepipes(act, data);
	initfdi(&act.fd_in, act.infile);
	if (act.append)
		initfdoa(&act.fd_out, act.outfile);
	else
		initfdo(&act.fd_out, act.outfile);
	executep(act, data);
}

//Espera a todos los hijos
void	espera(t_data *data, int *pids)
{
	int	i;
	int	status;

	i = 0;
	while (i < data->n_actions)
	{
		waitpid(pids[i], &status, 0);
		if (i == data->n_actions - 1)
		{
			if (WIFEXITED(status))
				data->xstatus = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				data->xstatus = 128 + WTERMSIG(status);
		}
		i++;
	}
}

//Itera las acciones para ejecutarlas
void	exactions(t_data *data)
{
	int	i;
	int	*pid;

	i = 0;
	if (data->n_actions == 1 && is_builtin((data->actions[0]).argv[0]))
		execute_builtin((data->actions[0]).argv, data);
	else
	{
		data->pipes = mempipas(data->n_actions);
		if (initpipes(data->pipes, data->n_actions) == 0)
			exit(1);
		pid = (int *)ft_calloc(sizeof(int), (data->n_actions + 1));
		while (i <= data->n_actions - 1)
		{
			pid[i] = fork();
			if (!pid[i])
				exactionp(data->actions[i], data);
			i++;
		}
		closepipes(data);
		espera(data, pid);
		free(pid);
		liberapipes(data->pipes, data->n_actions);
	}
}
*/
#include "minishell.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

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

//Error de no path
void	ft_nopath(void)
{
	ft_putstr_fd("PATH env not set\n", 2);
	exit(127);
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

//Ejecuta ruta directa
void	directexec(t_action act, t_data*minishell)
{
	int	excode;

	excode = 0;
	is_dir(act.argv[0]);
	existcmd(act.argv[0]);
	is_exec(act.argv[0]);
	excode = execve(act.argv[0], act.argv, minishell->env);
	exit(excode);
}

//executa un pipecomand
void	executep(t_action act, t_data*minishell)
{
	char	*path;
	int		excode;

	excode = 0;
	if (is_builtin(act.argv[0]))
	{
		execute_builtin(act.argv, minishell);
		exit(minishell->xstatus);
	}
	else
	{
		if (ft_strchr(act.argv[0], '/'))
			directexec(act, minishell);
		path = get_path(act.argv[0], minishell->env);
		if (!path)
			existcmd(act.argv[0]);
		excode = execve(path, act.argv, minishell->env);
		if (excode == -1)
		{
			printf("Fallo execve\n");
			free(path);
			exit(127);
		}
	}
}


//Ejecuta pipe(ultimo)
void	exactionp(t_action act, t_data *data)
{
	preparepipes(act, data);
	if (act.heredoc && act.heredoc_fd != -1)
	{
		dup2(act.heredoc_fd, STDIN_FILENO);
		close(act.heredoc_fd);
	}
	else
		initfdi(&act.fd_in, act.infile);
	if (act.append)
		initfdoa(&act.fd_out, act.outfile);
	else
		initfdo(&act.fd_out, act.outfile);
	executep(act, data);
}


//Espera a todos los hijos
void	espera(t_data *data, int *pids)
{
	int	i;
	int	status;

	i = 0;
	while (i < data->n_actions)
	{
		waitpid(pids[i], &status, 0);
		if (i == data->n_actions - 1)
		{
			if (WIFEXITED(status))
				data->xstatus = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				data->xstatus = 128 + WTERMSIG(status);
		}
		i++;
	}
}

static void	close_heredocs_parent(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_actions)
	{
		if (data->actions[i].heredoc_fd != -1)
		{
			close(data->actions[i].heredoc_fd);
			data->actions[i].heredoc_fd = -1;
		}
		i++;
	}
}

static int	redir_in_parent(t_action *act)
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

static int	redir_out_parent(t_action *act)
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

static int	exec_builtin_parent(t_action *act, t_data *data)
{
	int	save_in;
	int	save_out;

	save_in = dup(STDIN_FILENO);
	save_out = dup(STDOUT_FILENO);
	if (save_in < 0 || save_out < 0)
		return (1);
	if (redir_in_parent(act) || redir_out_parent(act))
	{
		perror("minishell");
		data->xstatus = 1;
		dup2(save_in, STDIN_FILENO);
		dup2(save_out, STDOUT_FILENO);
		close(save_in);
		close(save_out);
		return (1);
	}
	execute_builtin(act->argv, data);
	dup2(save_in, STDIN_FILENO);
	dup2(save_out, STDOUT_FILENO);
	close(save_in);
	close(save_out);
	return (0);
}

//Itera las acciones para ejecutarlas
void	exactions(t_data *data)
{
	int	i;
	int	*pid;

	i = 0;
	if (data->n_actions == 1 && is_builtin((data->actions[0]).argv[0]))
	{
		exec_builtin_parent(&data->actions[0], data);
		return ;
	}
	data->pipes = mempipas(data->n_actions);
	if (initpipes(data->pipes, data->n_actions) == 0)
		exit(1);
	pid = (int *)ft_calloc(sizeof(int), (data->n_actions + 1));
	while (i <= data->n_actions - 1)
	{
		pid[i] = fork();
		if (!pid[i])
			exactionp(data->actions[i], data);
		i++;
	}
	close_heredocs_parent(data);
	closepipes(data);
	espera(data, pid);
	free(pid);
	liberapipes(data->pipes, data->n_actions);
}

