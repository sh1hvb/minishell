/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 12:35:11 by smarsi            #+#    #+#             */
/*   Updated: 2024/08/01 14:41:32 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_heredoc(t_lexer *lst)
{
	char	delimiter;

	if (lst && lst->prev && lst->prev->type == 'H')
		return (1);
	if (lst && lst->in_quotes)
	{
		delimiter = '\"';
		if (lst->type == '\'')
			delimiter = '\'';
		while (lst && lst->value[0] != delimiter)
			lst = lst->prev;
		if (lst && lst->value[0] == delimiter)
			if (lst->prev && lst->prev->type == 'H')
				return (1);
	}
	return (0);
}

char	*my_strjoin2(char *s1, char *s2)
{
	char	*str;
	int		len;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (my_strdup(s2));
	else if (!s2)
		return (my_strdup(s1));
	len = (ft_strlen(s1) + ft_strlen(s2)) + 1;
	str = ft_malloc(len * sizeof(char), 0);
	if (!str)
		return (str);
	str[0] = '\0';
	ft_strlcat(str, s1, ft_strlen(s1) + 1);
	ft_strlcat(str, s2, len);
	free(s1);
	return (str);
}
