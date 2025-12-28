/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initfd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epascual <epascual@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 12:18:24 by epascual          #+#    #+#             */
/*   Updated: 2025/12/28 12:18:51 by epascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Inicia fd output
int	initfdo(int*fdout, char *doc)
{
	int	fdo;

	fdo = 1;
	if (doc && *doc)
		fdo = checkoutput(doc);
	*fdout = fdo;
	dup2(*fdout, 1);
	return (0);
}

//Inicia fdinput
int	initfdi(int*fdin, char *doc)
{
	int	fdi;

	fdi = 0;
	if (doc && *doc)
		fdi = checkinput(doc);
	*fdin = fdi;
	dup2(*fdin, 0);
	return (0);
}

//Inicia fd outputappend
int	initfdoa(int*fdout, char *doc)
{
	int	fdo;

	fdo = 1;
	if (doc && *doc)
		fdo = checkoutappend(doc);
	*fdout = fdo;
	dup2(*fdout, 1);
	return (0);
}
