#include "minishell.h"

//Abre el heredoc con delimitador y intenta redireccionar
void	heredoc(t_token *hdoc)
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
