/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:45:19 by mchihab           #+#    #+#             */
/*   Updated: 2023/11/16 21:49:19 by mchihab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	cnt(int n)
{
	int	count;

	count = 1;
	if (n < 1)
	{
		n *= -1;
		count++;
	}
	while (n >= 10)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static void	insert(char *p, int n, int len)
{
	int	a;

	a = len;
	if (n < 0)
	{
		n *= -1;
		p[0] = '-';
	}
	while (len)
	{
		if (n == 0)
			break ;
		(p[--len]) = n % 10 + 48;
		n = n / 10;
	}
	p[a] = '\0';
}

char	*ft_itoa(int n)
{
	char	*p;
	int		count;

	p = NULL;
	count = cnt(n);
	if (n == -2147483648)
	{
		return (ft_strdup("-2147483648"));
	}
	if (n == 0)
	{
		return (ft_strdup("0"));
	}
	p = malloc(count + 1 * sizeof(char));
	if (!p)
		return (NULL);
	insert(p, n, count);
	return (p);
}

// int	main(void)
// {
// 	long	num;
// 	char	*str;

// 	num = 0;
// 	str = ft_itoa(num);
// 	// char *str1 = _itoa(num);
// 	if (str)
// 	{
// 		printf("Integer: %ld\n", num);
// 		printf("String: %s\n", str);
// 		// printf("Integer: %d\n", num);
// 		// printf("String: %s\n", str1);
// 		free(str);
// 	}
// 	else
// 	{
// 		printf("Memory allocation failed.\n");
// 	}
// 	return (0);
// }
