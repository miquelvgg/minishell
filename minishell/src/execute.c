#include "minishell.h"

void	execute(t_data *minishell)
{
	printf("%s\n",minishell->token->data);
	char	*path;
	int		excode;
	char	**s_cmd;

	s_cmd = ft_split(minishell->token->data, ' ');
	if (is_builtin(s_cmd[0]))
			execute_builtin(s_cmd, minishell);
	else
	{
	path = get_path(s_cmd[0], minishell->env);
	excode = execve(path, s_cmd, NULL);
	}
/*	if (excode != 0)
	{
		ft_free_pointstring(s_cmd);
		//finish(excode);
	}*/
}
/*
An  interactive  shell is one started without non-option arguments (unless -s is specified) and
without the -c option whose standard input and error are both connected to terminals (as deter‐
mined  by  isatty(3)), or one started with the -i option.  PS1 is set and $- includes i if bash
is interactive, allowing a shell script or a startup file to test this state.

When an interactive login shell exits, or a  non-interactive  login  shell  executes  the  exit
builtin command, bash reads and executes commands from the file ~/.bash_logout, if it exists. 
*/

/*	man 7 signal
	SIGINT (2): interrupción de teclado (Ctrl-C)
	SIGQUIT (3): salida de teclado (Ctrl-\)
*/

int g_status ;
// handler function :p
void	reset_prompt(int signo)
{
	(void)signo;
	write (1, "\n", 1);
	//rl_on_new_line();
	//rl_replace_line("");
	//rl_display();
}

void	exect_interactive(t_data *data)
{
	(void)data;
	//Cambiar al execute
	/*	struct sigaction	act;
	
	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
	act.sa_handler = &reset_prompt;
	sigaction(SIGINT, &act, NULL);
	data->user_input = readline(PROMPT);
	if (data->user_input == NULL)
	{
		free_data(data, TRUE);
		exit(0);
	}
	act.sa_handler = &signal_print_newline;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
	if (*data->user_input && data->user_input)
		add_history(data->user_input);
	if (parse_input(data) == TRUE)
		g_status = execute(data);
	else
		g_status = 1;
	free_data(data, FALSE);
	*/
}
