#include "minishell.h"

void	exectscript(t_data *data)
{
	data->is_interactive = 0;
	printf("Script\n");
}

void	exectnointeractive(t_data *data)
{
	data->is_interactive = 0;
	printf("Oneline\n");
}

void	non_interactive(t_data *data, int argc, char **argv)
{

	if ((argc == 2) && (ft_strcmp(argv[1],"-c") == 0))
	{
		exectnointeractive(data);
	}
	if ((argc == 2) && (ft_strcmp(argv[1],"minishell") == 0))
	{
		exectscript(data);
	}
}
