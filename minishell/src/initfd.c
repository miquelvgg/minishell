#include "minishell.h"

int	initfdo(int*fdout, char *doc)
{
	int	fdo;

	fdo = 1;
	if (doc)
		fdo = checkoutput(doc);
	*fdout = fdo;
	dup2(*fdout, 1);
	return (0);
}

int	initfdi(int*fdin, char *doc)
{
	int fdi;

	fdi = 0;
	if (doc)
		fdi = checkinput(doc);
	*fdin = fdi;
	dup2(*fdin, 0);
	return (0);
}

int	initfdoa(int*fdout, char *doc)
{
	int fdo;

	fdo = 1;
	if (doc)
		fdo = checkoutappend(doc);
	*fdout = fdo;
	dup2(*fdout, 1);
	return (0);
}
