/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 20:17:46 by mchihab           #+#    #+#             */
/*   Updated: 2024/07/26 20:18:54 by mchihab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	nb_args(char **args)
{
	int	size;

	size = 0;
	while (args[size])
		size++;
	return (size);
}

void	ft_echo(t_data *data)
{
	int	i;
	int	n_option;
	int	j;

	i = 1;
	n_option = 0;
	j = 0;
	if (nb_args(data->args) > 1)
	{
		while (data->args[i])
		{
			j = 0;
			if (data->args[i][j] == '-' && data->args[i][j + 1] == 'n')
			{
				j++;
				while (data->args[i][j] == 'n')
				{
					n_option = 1;
					j++;
				}
				if (data->args[i][j] && data->args[i][j] != 'n')
				{
					if (i == 1)
						n_option = 0;
					break ;
				}
			}
			else
				break ;
			i++;
		}
		while (data->args[i])
		{
			j = 0;
			while (data->args[i][j])
			{
				write(1, &data->args[i][j], 1);
				j++;
			}
			if (data->args[i + 1])
				write(1, " ", 1);
			i++;
		}
	}
	if (n_option == 0)
		write(1, "\n", 1);
	env->exit_status = 0;
}
