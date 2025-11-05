/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   femtoshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epascual <epascual@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:10:32 by epascual          #+#    #+#             */
/*   Updated: 2025/10/28 15:11:00 by epascual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	main(int c, char **argv, char **env)
{
	c = 0;
	argv = 0;
	execve("/bin/bash", argv, env);
	return (0);
}
