/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvives-s <mvives-s@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:09:34 by mvives-s          #+#    #+#             */
/*   Updated: 2024/10/30 12:09:42 by mvives-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 2048
#endif

#ifndef OPEN_MAX
# define OPEN_MAX 1024
#endif

static char	*get_line(char *stash)
{
	size_t	i;
	char	*line;

	if (!stash || !*stash)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		line = ft_substr(stash, 0, i + 1);
	else
		line = ft_substr(stash, 0, i);
	return (line);
}

static char	*save_stash(char *stash)
{
	size_t	i;
	char	*new_stash;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	new_stash = ft_substr(stash, i + 1, ft_strlen(stash) - i - 1);
	free(stash);
	return (new_stash);
}

static char	*read_and_stash(int fd, char *stash)
{
	char	*buf;
	ssize_t	bytes_read;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(stash, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[bytes_read] = '\0';
		stash = ft_strjoin(stash, buf);
		if (!stash)
		{
			free(buf);
			return (NULL);
		}
	}
	free(buf);
	return (stash);
}

char	*ft_get_next_line(int fd)
{
	static char	*stash[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= OPEN_MAX)
		return (NULL);
	stash[fd] = read_and_stash(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = get_line(stash[fd]);
	stash[fd] = save_stash(stash[fd]);
	return (line);
}
/*
#include <stdio.h>
#include <fcntl.h>
int main() {
	
	int		fd[3];		
	char	*buffer = NULL;
	int 	count;
	int		i;
	int 	fd_view;


	count = 0;
	fd[0] = open("1.txt", O_RDONLY);
	if (fd[0] == -1)
		return (1);
	fd[1] = open("2.txt", O_RDONLY);
	if (fd[1] == -1)
		return (1);
	fd[2] = open("3.txt", O_RDONLY);
	if (fd[2] == -1)
		return (1);
		
	i=0;	
	fd_view = (i%3);
//	printf("\n (%d) \n",fd_view);
	buffer = get_next_line(fd[fd_view]);
	while ((buffer != NULL) && (buffer[0] != '\0'))
	{
		i++;
		printf("%s", buffer);
		if (buffer)
			free(buffer);
		fd_view = (i%3);
//		printf("\n (%d) \n",fd_view);
		buffer = get_next_line(fd[fd_view]);
		count++;
	}
	close(fd[0]);
	close(fd[1]);
	close(fd[2]);
	if (buffer)
		free(buffer);
	return (0);
}
*/
