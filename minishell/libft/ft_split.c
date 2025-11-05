/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvives-s <mvives-s@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 21:49:06 by mvives-s          #+#    #+#             */
/*   Updated: 2024/09/29 21:49:13 by mvives-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_separator(char c, char sep)
{
	return (c == sep);
}

static size_t	n_word(char const *s, char sep)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && is_separator(s[i], sep))
			i++;
		if (s[i])
		{
			count++;
			while (s[i] && !is_separator(s[i], sep))
				i++;
		}
	}
	return (count);
}

static char	*g_next_word(char const *s, char sep, size_t *idx)
{
	size_t	ini;
	size_t	fin;
	size_t	i;
	char	*word;

	while (s[*idx] && is_separator(s[*idx], sep))
		(*idx)++;
	ini = *idx;
	while (s[*idx] && !is_separator(s[*idx], sep))
		(*idx)++;
	fin = *idx;
	word = (char *)malloc(sizeof(char) * (fin - ini + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (ini < fin)
	{
		word[i++] = s[ini++];
	}
	word[i] = '\0';
	return (word);
}

static void	f_arr(char **arr, size_t j)
{
	size_t	i;

	i = 0;
	while (i < j)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	**ft_split(char const *s, char sep)
{
	size_t	word_count;
	size_t	i;
	size_t	index;
	char	**p_array;

	if (s == NULL)
		return (NULL);
	word_count = n_word(s, sep);
	p_array = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!p_array)
		return (NULL);
	index = 0;
	i = 0;
	while (i < word_count)
	{
		p_array[i] = g_next_word(s, sep, &index);
		if (p_array[i] == NULL)
		{
			f_arr(p_array, i);
			return (NULL);
		}
		i++;
	}
	p_array[i] = NULL;
	return (p_array);
}
