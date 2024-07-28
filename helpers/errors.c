/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 18:02:25 by smarsi            #+#    #+#             */
/*   Updated: 2024/07/27 18:02:26 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_error(char *msg, int ext)
{
	printf("%s\n", msg);
	return (ext);
}

void	ft_freed(char **p)
{
	int	i;

	i = 0;
	while (p[i])
	{
		free(p[i]);
		p[i++] = NULL;
	}
	free(p);
	p = NULL;
}
