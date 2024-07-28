/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_split_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 20:17:14 by mchihab           #+#    #+#             */
/*   Updated: 2024/07/28 13:36:52 by mchihab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	void	ft_free(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}

static	void	get_word_norm(char *src, int *index, char *delimiters)
{
	int	i;

	i = *index;
	while (src[i] && !in_delimiters(src[i], delimiters))
	{
		i++;
		if (src[i] == '\"')
		{
			split_quotes(src, '\"', &i);
			while (src[i] && !in_delimiters(src[i], " \t\n"))
				i++;
		}
		else if (src[i] == '\'')
		{
			split_quotes(src, '\'', &i);
			while (src[i] && !in_delimiters(src[i], " \t\n"))
				i++;
		}
	}
	*index = i;
}

static char	*get_word(char *dst, char *src, char *delimiters, int *index)
{
	int	i;
	int	start;
	int	len;

	i = *index;
	while (src[i] && in_delimiters(src[i], delimiters))
		i++;
	start = i;
	if (src[i] == '\"' || src[i] == '\'')
	{
		split_quotes(src, src[i], &i);
		while (src[i] && !in_delimiters(src[i], " \t\n"))
			i++;
	}
	else
		get_word_norm(src, &i, delimiters);
	len = (i - start) + 1;
	dst = ft_calloc(len, sizeof(char));
	(ft_strlcpy(dst, src + start, len), *index = i);
	return (dst);
}

char	**fill_array_b(char **dst, char *src, char *delimiters, int num_word)
{
	int	i;
	int	index_word;

	index_word = 0;
	i = 0;
	while (i < num_word)
	{
		dst[i] = get_word(dst[i], src, delimiters, &index_word);
		if (!dst[i])
			ft_free(dst);
		i++;
	}
	return (dst);
}
