#include "minishell.h"

int	initfdo(t_data*shell, char *doc)
{
	int	fdo;

	fdo = 1;
	fdo = checkoutput(doc);
	shell->fdout = fdo;
	dup2(shell->fdout, 1);
	return (0);
}

int	initfdi(t_data*shell, char *doc)
{
	int fdi;

	fdi = 0;
	fdi = checkinput(doc);
	shell->fdin = fdi;
	dup2(shell->fdin, 0);
	return (0);
}

int	initfdoa(t_data*shell, char *doc)
{
	int fdo;

	fdo = 1;
	fdo = checkoutappend(doc);
	shell->fdout = fdo;
	dup2(shell->fdout, 1);
	return (0);
}
