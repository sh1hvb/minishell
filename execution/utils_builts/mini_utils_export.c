/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 20:08:30 by mchihab           #+#    #+#             */
/*   Updated: 2024/07/30 19:30:01 by mchihab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ascending(int a, int b)
{
	return (a <= b);
}

int	if_flag(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	check_equal(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
		{
			return (1);
		}
		i++;
	}
	return (0);
}

void	handle_no_arguments(t_envp *env)
{
	t_envp	*a;
	char	**g;

	g = list_to_pointer();
	a = sort_list(env, ascending);
	print_env_list(a, "ex");
	ft_lstclear_env(g_env);
	g_env = get_env(g, 1);
	ft_freed(g);
}

int	handle_no_first_element(char **arr)
{
	if (!arr[0])
	{
		// ft_freed(arr);
		return (1);
	}
	return (0);
}
