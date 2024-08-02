/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_checker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 20:13:15 by mchihab           #+#    #+#             */
/*   Updated: 2024/08/02 21:16:22 by mchihab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_builts(t_data *data)
{
	if (!data->cmd || !data->args)
		return (0);
	if (!ft_strcmp(data->cmd, "echo"))
		return (1);
	else if (!ft_strcmp(data->cmd, "cd"))
		return (2);
	else if (!ft_strcmp(data->cmd, "pwd"))
		return (3);
	else if (!ft_strcmp(data->cmd, "export"))
		return (4);
	else if (!ft_strcmp(data->cmd, "unset"))
		return (5);
	else if (!ft_strcmp(data->cmd, "env"))
		return (6);
	else if (!ft_strcmp(data->cmd, "exit"))
		return (7);
	return (0);
}

void	handle_builts(t_data *data)
{
	t_envp	*envtmp;

	envtmp = g_env;
	if (!check_builts(data))
		ft_error(" command not found", 127);
	if (check_builts(data) == 1)
		ft_echo(data);
	if (check_builts(data) == 2)
		ft_cd(data);
	if (check_builts(data) == 3)
		ft_pwd(data);
	if (check_builts(data) == 4)
		ft_export(data, envtmp);
	if (check_builts(data) == 5)
		ft_unset(data->args);
	if (check_builts(data) == 6)
		ft_env();
	if (check_builts(data) == 7)
		ft_exit(data);
}

int	check_key(char *s)
{
	t_envp	*d;

	d = g_env;
	while (d)
	{
		if (!ft_strcmp(d->key, s))
			return (1);
		d = d->next;
	}
	return (0);
}

void	ft_err_export(char *s)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(s, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	g_env->exit_status = 1;
}
