/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvives-s <mvives-s@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:11:41 by mvives-s          #+#    #+#             */
/*   Updated: 2024/09/18 10:12:20 by mvives-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

// Variable global para el estado (solo si es estrictamente necesario)
int	g_signal;

// SIGINT = Ctrl+C
// Avisa a readline que estamos en nueva linea
// Limpia lo que el usuario escribió
// Muestra el prompt de nuevo
void	handle_signals(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = SIGINT;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		if (rl_line_buffer && *rl_line_buffer != '\0')
		{
			g_signal = SIGQUIT;
		}
	}
}

//sa.sa_flags = SA_RESTART; 
// Evita que algunas system calls fallen
// Capturamos Ctrl+C
// Ignoramos Ctrl+\ (SIGQUIT no debe hacer nada en el prompt)
void	setup_signals(void)
	{
	struct sigaction	sa;

	sa.sa_handler = &handle_signals;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}
