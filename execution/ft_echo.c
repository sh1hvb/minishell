/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 20:17:46 by mchihab           #+#    #+#             */
/*   Updated: 2024/07/28 13:36:04 by mchihab          ###   ########.fr       */
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

int	check_n_option(char **args, int *n_option)
{
	int	i;
	int	j;

	i = 1;
	*n_option = 0;
	while (args[i])
	{
		j = 0;
		if (args[i][j] == '-' && args[i][j + 1] == 'n')
		{
			j++;
			while (args[i][j] == 'n')
				j++;
			if (args[i][j] != '\0')
				break ;
			*n_option = 1;
		}
		else
			break ;
		i++;
	}
	return (i);
}

void	print_args(char **args, int start_index)
{
	int	i;
	int	j;

	i = start_index;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			write(1, &args[i][j], 1);
			j++;
		}
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
}

void	ft_echo(t_data *data)
{
	int	i;
	int	n_option;

	n_option = 0;
	if (nb_args(data->args) > 1)
	{
		i = check_n_option(data->args, &n_option);
		print_args(data->args, i);
	}
	if (n_option == 0)
		write(1, "\n", 1);
	env->exit_status = 0;
}
