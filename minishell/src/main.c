/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvives-s <mvives-s@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:11:41 by mvives-s          #+#    #+#             */
/*   Updated: 2026/01/01 19:21:46 by epascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Imprime acciones
void	free_data_struc(t_data *dt)
{
	int	i;

	if (!dt->token)
		return ;
	i = 0;
	while (dt->token[i] != NULL)
	{
		if (dt->token[i]->data)
		{
			free(dt->token[i]->data);
			dt->token[i]->data = NULL;
		}
		if (dt->token[i])
		{
			free(dt->token[i]);
			dt->token[i] = NULL;
		}
		i++;
	}
	if (dt->token != NULL)
		free(dt->token);
}

int	ft_control(int argc, char **argv)
{
	(void)argv;
	if (argc != 1)
		return (1);
	if (!isatty(STDIN_FILENO))
	{
		ft_putstr_fd("Error: No redireccionar la entrada estándar.\n", 2);
		return (2);
	}
	if (!isatty(STDOUT_FILENO))
	{
		ft_putstr_fd("Error: No redireccionar la salida estándar.\n", 2);
		return (3);
	}
	return (0);
}

//Inicia data
int	init_var(t_data	*data)
{
	data->token = NULL;
	data->actions = NULL;
	data->user_input = NULL;
	data->env = NULL;
	data->argv = NULL;
	data->working_dir = NULL;
	data->old_working_dir = NULL;
	data->xstatus = 0;
	return (0);
}

//Main, inicia env
int	main(int argc, char **argv, char **env)
{
	t_data	data;
	int		res;

	if (ft_control(argc, argv))
		return (1);
	if (!isatty(STDOUT_FILENO))
	{
		ft_putstr_fd("Error: No redireccionar la salida estándar.\n", 2);
		return (1);
	}
	res = init_var(&data);
	data.env = create_first_env(env);
	if (!res)
		res = mshell(&data);
	exit_var(&data);
	return (0);
}
