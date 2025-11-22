#include "minishell.h"

int	initfd(t_data*shell)
{
	int fdi;
	int	fdo;

	shell->fdin = 0;
	fdi = checkinput("makefile");
	shell->fdin = fdi;
	shell->fdout = 1;
	fdo = checkoutput("output");
	shell->fdin = fdo;
	return (0);
}

