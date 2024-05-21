/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 06:45:30 by smarsi            #+#    #+#             */
/*   Updated: 2024/05/21 11:25:25 by mchihab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error(char *msg, int ext)
{
	printf("%s", msg);
	exit(ext);
}

void ft_freed(char **p)
{
	int i = 0;
	while(p[i])
	{
		free(p[i++]);
	}
	free(p);
}
