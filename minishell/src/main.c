/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvives-s <mvives-s@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:11:41 by mvives-s          #+#    #+#             */
/*   Updated: 2025/12/30 11:50:57 by epascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
void	print_actions(t_data *d)
{
	int		i;
	int		j;
	t_action *act;

	if (!d) {
		printf("print_actions: data es NULL\n");
		return;
	}
	if (!d->actions || d->n_actions <= 0) {
		printf("print_actions: no hay acciones\n");
		return;
	}
	
	printf("===== ACCIONES (total: %d) =====\n", d->n_actions);
	i = 0;
	while (i < d->n_actions)
	{
		act = &d->actions[i];
		printf("---- Acción %d ----\n", i);
		printf("index   : %d\n", act->index);

		printf("argv    : ");
		if (!act->argv)
			printf("(null)\n");
		else 
		{
			j = 0;
			while (act->argv[j])
			{
				printf("[%d] \"%s\"  ", j, act->argv[j]);
				j++;
      		}
		if (j == 0)
			printf("(vacío)");
		printf("\n");
	}

	printf("infile  : %s\n", act->infile ? act->infile : "(null)");
	printf("outfile : %s\n", act->outfile ? act->outfile : "(null)");
	printf("append  : %d\n", act->append);


	printf("fd_in   : %d\n", act->fd_in);
	printf("fd_out  : %d\n", act->fd_out);

	printf("--------------------\n");
	i++;
	}
	printf("===== FIN ACCIONES =====\n");
}

//Libera el data struct

//Imprime los tokens
void paint_token(t_data	*data)
{
	int		i;
	t_token **mtoken;
	
	i = 0;
	if (!data->token)
    	return;
	mtoken = data->token;
	
	while ((mtoken[i] != NULL))
	{
		printf("(%d) %s \n", i, mtoken[i]->data);
		i++;
	}
}
*/

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
		fprintf(stderr,
			"Error: No se permite redireccionar la entrada estándar.\n");
		return (2);
	}
	if (!isatty(STDOUT_FILENO))
	{
		fprintf(stderr,
			"Error: No se permite redireccionar la salida estándar.\n");
		return (3);
	}
	return (0);
}

//Inicia data
int	init_var(t_data	*data)
{
	data->signal_status = 0;
	data->token = NULL;
	data->actions = NULL;
	data->fdin = 0;
	data->fint = 0;
	data->fdout = 0;
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
		fprintf(stderr,
			"Error: No se permite redireccionar la salida estándar.\n");
		return (1);
	}
	res = init_var(&data);
	data.env = create_first_env(env);
	if (!res)
		res = mshell(&data);
	exit_var(&data);
	return (0);
}
