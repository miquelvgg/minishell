/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epascual <epascual@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 17:54:06 by epascual          #+#    #+#             */
/*   Updated: 2025/12/29 17:54:09 by epascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Comprueba que se pueda abrir el input y devuelve el fd
int	checkinput(char *path)
{
	int	fd;

	fd = 0;
	if (path && *path)
	{
		if (access(path, R_OK) == 0)
		{
			fd = open(path, 0, O_RDONLY);
			if (fd < 0)
			{
				close(fd);
				exit(errno);
			}
		}
		else
			printf("Not readable");
	}
	return (fd);
}
/*//Main de prueba
int main(int ac, char**av)
{
	int fd;

	if (ac > 1)
		fd = checkinput(av[1]);
	printf("%i", fd);
	return (0);
}*/

//Prueba que se pueda abrir el output
int	checkoutput(char *path)
{
	int	fd;

	fd = 1;
	if (path && *path)
	{
		fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (fd < 0)
		{
			printf("Could not create file");
			fd = 1;
		}
	}
	return (fd);
}

//Prueba que se pueda abrir el output en modo append
int	checkoutappend(char *path)
{
	int	fd;

	fd = 0;
	if (path && *path)
	{
		if (access(path, W_OK) == 0)
		{
			fd = open(path, 0, O_CREAT | O_APPEND);
			if (fd < 0)
			{
				printf("Not opened");
				close(fd);
				exit(errno);
				fd = 0;
			}
		}
	}
	return (fd);
}
