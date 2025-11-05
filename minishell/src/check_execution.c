#include "minishell.h"

int	check_execution(t_data *data, int argc, char **argv)
{
	if (argc == 1)
		data->is_interactive = 1;
	else if (argc == 3)
		data->is_interactive = 0;
		// ahora se habrian de controlar las otras mariqueras
	else
	{
		ft_printf ("Numero de argumento incorrecto");
		return (1);
	}
	argv = 0;
	return (0);
}
