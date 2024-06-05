/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:55:30 by smarsi            #+#    #+#             */
/*   Updated: 2024/05/23 11:28:46 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char  *s1, char  *s2)
{
	char	*p;
	int		i;
	int		j;
	size_t	lens1;
	size_t	lens2;

	if (!s1 || !s2)
		return (0);
	lens1 = ft_strlen((char *)s2);
	lens2 = ft_strlen((char *)s1);
	p = (char *)malloc(sizeof(char) * lens1 + lens2 + 1);
	if (!p)
		return (0);
	i = -1;
	while (s1[++i])
		p[i] = s1[i];
	j = -1;
	while (s2[++j])
		p[i++] = s2[j];
	p[i] = '\0';
	return (p);
}
