#include "minishell.h"
void	execute(t_data *minishell)
{
	(void)minishell;
	printf("%s\n",minishell->token->data);

}
