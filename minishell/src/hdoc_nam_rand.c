/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc_nam_rand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvives-s <mvives-s@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:11:41 by mvives-s          #+#    #+#             */
/*   Updated: 2024/09/18 10:12:20 by mvives-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	read_urandom(unsigned char *buf, int n)
{
	int	fd;
	int	r;
	int	got;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0)
		return (-1);
	got = 0;
	while (got < n)
	{
		r = read(fd, buf + got, n - got);
		if (r <= 0)
			return (close(fd), -1);
		got += r;
	}
	return (close(fd), 0);
}

static void	to_hex(char *dst, const unsigned char *src, int n)
{
	const char	*hex = "0123456789abcdef";
	int			i;

	i = 0;
	while (i < n)
	{
		dst[i * 2] = hex[(src[i] >> 4) & 0xF];
		dst[i * 2 + 1] = hex[src[i] & 0xF];
		i++;
	}
	dst[n * 2] = '\0';
}

void	build_path(char *path, const char *prefix, const char *suffix)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (prefix[i])
	{
		path[i] = prefix[i];
		i++;
	}
	while (suffix[j])
	{
		path[i] = suffix[j];
		i++;
		j++;
	}
	path[i] = '\0';
}

int	hd_open_tmpfile(void)
{
	unsigned char	rnd[8];
	char			hex[17];
	char			path[128];
	int				fd;
	int				tries;

	tries = 0;
	while (tries < 100)
	{
		if (read_urandom(rnd, 8) < 0)
			return (-1);
		to_hex(hex, rnd, 8);
		build_path(path, "/tmp/mshell_hd_", hex);
		fd = open(path, O_RDWR | O_CREAT | O_EXCL, 0600);
		if (fd >= 0)
		{
			unlink(path);
			return (fd);
		}
		if (errno != EEXIST)
			return (-1);
		tries++;
	}
	return (-1);
}

int	hd_open_tmpfile_2fds(int *fd_r, int *fd_w)
{
	unsigned char	rnd[8];
	char			hex[17];
	char			path[64];
	int				tries;

	if (!fd_r || !fd_w)
		return (-1);
	*fd_r = -1;
	*fd_w = -1;
	tries = 0;
	while (tries < 100)
	{
		if (read_urandom(rnd, 8) < 0)
			return (-1);
		to_hex(hex, rnd, 8);
		build_path(path, "/tmp/ms_hd_", hex);
		if (hd_open_2fds_at_path(path, fd_r, fd_w) == 0)
			return (0);
		if (errno != EEXIST)
			return (-1);
		tries++;
	}
	return (-1);
}
