/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 12:44:24 by mchihab           #+#    #+#             */
/*   Updated: 2023/11/15 17:29:46 by mchihab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*p;

	if (!s)
		return (0);
	i = 0;
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	else if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	p = (char *)malloc((len + 1) * sizeof(char));
	if (!p)
		return (0);
	while (i < len && s[i] && start <= ft_strlen(s))
	{
		p[i] = s[start];
		if (!p[i])
			return (0);
		start++;
		i++;
	}
	p[i] = '\0';
	return (p);
}
// int main()
// {
//     printf("%s",ft_substr("",0,1));

// // ft_substr("habibi",1,500) -===> 6
// // ft_substr("habibi",1,3) -===> 4
// // ila kan lenn kbr mn ft_strlen(s + start)
// }
// // ila kan lenn sghr mn ft_strlen(s + start)
// // }