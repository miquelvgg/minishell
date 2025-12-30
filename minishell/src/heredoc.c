#include "minishell.h"



static void	hd_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	_exit(130);
}

static int	hd_is_quoted(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = ft_strlen(s);
	if (len < 2)
		return (0);
	if ((s[0] == '\'' && s[len - 1] == '\'')
		|| (s[0] == '"' && s[len - 1] == '"'))
		return (1);
	return (0);
}

static char	*hd_strip_quotes(const char *delim, int *expand)
{
	size_t	len;

	*expand = 1;
	if (!delim)
		return (NULL);
	len = ft_strlen(delim);
	if (!hd_is_quoted(delim))
		return (ft_strdup(delim));
	*expand = 0;
	return (ft_substr(delim, 1, len - 2));
}

static int	hd_is_var_start(char c)
{
	return (ft_isalpha(c) || c == '_');
}

static int	hd_is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

static const char	*hd_getenv(t_data *data, const char *key, size_t klen)
{
	int		i;
	char	*env;

	if (!data || !data->env || !key || klen == 0)
		return (NULL);
	i = 0;
	while (data->env[i])
	{
		env = data->env[i];
		if (ft_strncmp(env, key, klen) == 0 && env[klen] == '=')
			return (env + klen + 1);
		i++;
	}
	return (NULL);
}

static size_t	hd_nbr_len(unsigned int n)
{
	size_t	len;

	len = 1;
	while (n >= 10)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	hd_write_nbr(char *dst, unsigned int n, size_t *k)
{
	char	tmp[10];
	size_t	i;

	i = 0;
	while (n >= 10)
	{
		tmp[i++] = (char)('0' + (n % 10));
		n /= 10;
	}
	tmp[i++] = (char)('0' + n);
	while (i > 0)
		dst[(*k)++] = tmp[--i];
}

static size_t	hd_len_one(const char *s, size_t *i, t_data *data)
{
	size_t		j;
	size_t		klen;
	const char	*val;

	if (s[*i] == '$' && s[*i + 1] == '?')
	{
		*i += 2;
		return (hd_nbr_len((unsigned int)data->xstatus));
	}
	if (s[*i] == '$' && hd_is_var_start(s[*i + 1]))
	{
		j = *i + 1;
		while (s[j] && hd_is_var_char(s[j]))
			j++;
		klen = j - (*i + 1);
		val = hd_getenv(data, &s[*i + 1], klen);
		*i = j;
		if (val)
			return (ft_strlen(val));
		return (0);
	}
	(*i)++;
	return (1);
}

static size_t	hd_expand_len(const char *s, t_data *data)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (s && s[i])
		len += hd_len_one(s, &i, data);
	return (len);
}

static void	hd_copy_one(char *out, size_t *k, const char *s, size_t *i)
{
	out[(*k)++] = s[(*i)++];
}

static void	hd_copy_var(char *out, size_t *k, const char *val)
{
	while (val && *val)
		out[(*k)++] = *val++;
}

static void	hd_fill_one(char *out, size_t *k, const char *s, size_t *i,
		t_data *data)
{
	size_t		j;
	size_t		klen;
	const char	*val;

	if (s[*i] == '$' && s[*i + 1] == '?')
	{
		hd_write_nbr(out, (unsigned int)data->xstatus, k);
		*i += 2;
		return ;
	}
	if (s[*i] == '$' && hd_is_var_start(s[*i + 1]))
	{
		j = *i + 1;
		while (s[j] && hd_is_var_char(s[j]))
			j++;
		klen = j - (*i + 1);
		val = hd_getenv(data, &s[*i + 1], klen);
		*i = j;
		hd_copy_var(out, k, val);
		return ;
	}
	hd_copy_one(out, k, s, i);
}

static char	*hd_expand(const char *s, t_data *data)
{
	char	*out;
	size_t	i;
	size_t	k;

	out = (char *)malloc(hd_expand_len(s, data) + 1);
	if (!out)
		return (NULL);
	i = 0;
	k = 0;
	while (s && s[i])
		hd_fill_one(out, &k, s, &i, data);
	out[k] = '\0';
	return (out);
}

static int	hd_is_delim(const char *line, const char *delim)
{
	if (!line || !delim)
		return (0);
	return (ft_strncmp(line, delim, ft_strlen(delim) + 1) == 0);
}

static int	hd_open_tmp(int *fd)
{
	char	tmp[24];

	ft_strlcpy(tmp, "/tmp/ms_hdXXXXXX", sizeof(tmp));
	*fd = mkstemp(tmp);
	if (*fd < 0)
		return (1);
	unlink(tmp);
	return (0);
}

static void	hd_child_loop(int fd, const char *delim, int expand, t_data *data)
{
	char	*line;
	char	*out;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (hd_is_delim(line, delim))
		{
			free(line);
			break ;
		}
		if (expand)
			out = hd_expand(line, data);
		else
			out = ft_strdup(line);
		free(line);
		if (!out)
			break ;
		write(fd, out, ft_strlen(out));
		write(fd, "\n", 1);
		free(out);
	}
}

static void	hd_parent_ignore(void (**old_int)(int), void (**old_quit)(int))
{
	*old_int = signal(SIGINT, SIG_IGN);
	*old_quit = signal(SIGQUIT, SIG_IGN);
}

static void	hd_parent_restore(void (*old_int)(int), void (*old_quit)(int))
{
	signal(SIGINT, old_int);
	signal(SIGQUIT, old_quit);
}

static int	hd_wait_status(int fd, pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		close(fd);
		return (-2);
	}
	return (0);
}

static int	hd_prepare_one(t_action *act, t_data *data)
{
	int		fd;
	pid_t	pid;
	char	*delim;
	int		expand;
	void	(*old_int)(int);
	void	(*old_quit)(int);
	int		ret;

	if (hd_open_tmp(&fd))
		return (-1);
	delim = hd_strip_quotes(act->infile, &expand);
	if (!delim)
	{
		close(fd);
		return (-1);
	}
	hd_parent_ignore(&old_int, &old_quit);
	pid = fork();
	if (pid == -1)
	{
		hd_parent_restore(old_int, old_quit);
		free(delim);
		close(fd);
		return (-1);
	}
	if (pid == 0)
	{
		signal(SIGINT, hd_sigint);
		signal(SIGQUIT, SIG_IGN);
		hd_child_loop(fd, delim, expand, data);
		free(delim);
		close(fd);
		_exit(0);
	}
	ret = hd_wait_status(fd, pid);
	hd_parent_restore(old_int, old_quit);
	free(delim);
	if (ret < 0)
		return (ret);
	lseek(fd, 0, SEEK_SET);
	if (act->heredoc_fd != -1)
		close(act->heredoc_fd);
	act->heredoc_fd = fd;
	return (0);
}

int	ft_prepare_heredocs(t_data *data)
{
	int	i;
	int	ret;

	if (!data || !data->actions)
		return (0);
	i = 0;
	while (i < data->n_actions)
	{
		if (data->actions[i].heredoc)
		{
			ret = hd_prepare_one(&data->actions[i], data);
			if (ret < 0)
				return (ret);
		}
		i++;
	}
	return (0);
}
//Abre el heredoc con delimitador y intenta redireccionar
/*void	heredoc(t_token *hdoc)
{
	pid_t	pleer;
	int		fd[2];
	char	*linea;

	if (pipe(fd) < 0)
		exit(12);
	pleer = fork();
	if (pleer == 0)
	{
		close(fd[0]);
		linea = ft_get_next_line(0);
		while (linea)
		{
			if (ft_strncmp(linea, hdoc->data, ft_strlen(hdoc->data)) == 0)
			{
				free(linea);
				exit(0);
			}
			ft_putstr_fd(linea, fd[1]);
			free(linea);
			linea = ft_get_next_line(0);
		}
		close(fd[1]);
		exit(0);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
		wait(NULL);
	}
}
	*/
/*
//main de prueba cc heredoc.c -L . -ltf
int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <delimiter>\n", argv[0]);
        return 1;
    }
    t_token hdoc;
    hdoc.data = argv[1];  // Set delimiter from command line argument
    printf("Enter heredoc content, end with '%s':\n", hdoc.data);
    heredoc(&hdoc);
    // Now stdin is redirected to the pipe output, so we can read the heredoc content
    char *line;
    printf("Heredoc output:\n");
    while ((line = ft_get_next_line(0))) {
        printf("%s\n", line);
        free(line);
    }
    return 0;
}*/
