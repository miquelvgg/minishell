#include "minishell.h"

char *ft_freestrjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s1)
		s1 = ft_strdup("");
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
	{
		free(s1);
		return (NULL);
	}
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	j = -1;
	while (s2[++j])
		str[i + j] = s2[j];
	str[i + j] = '\0';
	free(s1);
	free(s2);
	return (str);
	
}
//itera los tokens y ejecuta
void	selexecute(t_data *shell)
{
	int		i;
	t_token	*actual;
	char	*cmd;

	i = 0;
	actual = shell->token[i];
	while (actual)
	{
		if (actual->type == 1)
		{
			cmd = actual->data;
			printf("//ejecuta comando o anade a string que ejecutara");
			execute(shell, cmd);
		}
		if (actual->type == 2)
		{
			printf("Abriendo input");
			initfdi(shell, actual->data);
		}
			//Abre fdin
		if (actual->type == 3)
		{
			printf("abriendo output");
			initfdo(shell, actual->data);
			//Abre fdout
		}
		if (actual->type == 4)
		{
			printf("Abre append output");
			initfdoa(shell, actual->data);
			//Abre fdoutappend
		}
			if (actual->type == 5)
		{
			printf("Abre heredoc");
			heredoc(actual);
			//printf("//Abre fdinheredoc");
		}
		i++;
		actual = shell->token[i];
	}
}
