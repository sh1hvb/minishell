/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 19:32:03 by smarsi            #+#    #+#             */
/*   Updated: 2024/07/29 17:03:18 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

long long	ft_atoi2(char *str)
{
	int		signe;
	size_t	digit;

	digit = 0;
	signe = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		signe = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (ft_isdigit(*str))
	{
		digit = (digit * 10 + *str) - '0';
		if ((signe >= 0 && digit > 9223372036854775807))
			return (0);
		else if ((signe < 0 && digit > 9223372036854775807))
			return (0);
		str++;
	}
	if (str && *str)
		return (0);
	return (1);
}

int	is_number(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '+' || arg[i] == '-')
			i++;
		while (in_delimiters(arg[i], " \t"))
			i++;
		if (!arg[i])
			return (0);
		while (arg[i] && arg[i] >= '0' && arg[i] <= '9')
			i++;
		while (arg[i] && in_delimiters(arg[i], " \t"))
			i++;
		if (arg[i])
			return (0);
	}
	return (1);
}

void	ft_exit(t_data *data)
{
	int	ext;

	ext = g_env->exit_status;
	if (data && !data->next)
	{
		ft_putstr_fd("exit\n", 1);
		if ((data->args && data->args[1]))
		{
			if (!data->args[1][0] || !ft_atoi2(data->args[1]))
			{
				ft_putstr_fd(my_strjoin("minishell: exit: ", data->args[1]), 2);
				ft_putstr_fd(": numeric argument required\n", 2);
				(ft_malloc(0, 1), ft_lstclear_env(g_env));
				exit(2);
			}
			else if (data->args[2])
			{
				(ft_putstr_fd("minishell: \
exit: too many arguments\n",
								2),
					g_env->exit_status = 1);
				return ;
			}
			ext = ft_atoi(data->args[1]);
		}
		(ft_malloc(0, 1), ft_lstclear_env(g_env), exit((char)ext));
	}
}
