/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:57:17 by smarsi            #+#    #+#             */
/*   Updated: 2024/05/22 12:48:27 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s1_dup;
	int		len;

	if (!s1)
		return (ft_strdup(""));
	len = ft_strlen(s1);
	s1_dup = ft_calloc(len + 1, sizeof(char));
	if (!s1_dup)
		return (NULL);
	ft_strlcpy(s1_dup, s1, len + 1);
	return (s1_dup);
}
