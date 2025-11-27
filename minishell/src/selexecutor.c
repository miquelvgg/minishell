#include "minishell.h"
void	selexecute(t_data *shell)
{
	int		i;
	t_token	*actual;

	i = 0;
	actual = shell->token[i];
	while (actual)
	{
		if (actual->type == 1)
		{execute(shell, actual->data);
		//rintf("//ejecuta comando o anade a string que ejecutara");
		}
		if (actual->type == 2)
			initfdi(shell, actual->data);
			//Abre fdin
		if (actual->type == 3)
			initfdo(shell, actual->data);
			//Abre fdout
		if (actual->type == 4)
			initfdoa(shell, actual->data);
			//Abre fdoutappend
		if (actual->type == 5)
			printf("//Abre fdinheredoc");
		i++;
		actual = shell->token[i];
	}
}
