/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:07:34 by smarsi            #+#    #+#             */
/*   Updated: 2024/05/18 10:58:39 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strchr(const char *s, char c)
{
	while (*s && *s != (char) c)
		s++;
	if (*s == (char) c)
		return ((char *) s);
	return (NULL);
}

char	*ft_strchrs(char *s, char *c)
{
    int i;

	while (*s && *s != (char) c[i])
	{
		i = 0;
		while (*s && c[i] && *s != (char) c[i])
			i++;
		if (*s == (char) c[i])
			break ;
		else
			s++;
	}
	if (*s == (char) c[i])
		return (s);
	return (NULL);
}
