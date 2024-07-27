/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 19:58:38 by mchihab           #+#    #+#             */
/*   Updated: 2024/07/26 19:58:39 by mchihab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	is_directory(char *path)
{
	int	fd;

	fd = open(path, __O_DIRECTORY);
	return (fd != -1 && (path[0] == '/' || (path[ft_strlen(path) - 1] == '/'
				&& (path[0] == '.') && path[1] == '/')));
}

void	handle_child_execution(t_data *data)
{
	if (!check_builts(data))
	{
		if (data && data->cmd)
			exec(data);
		ft_lstclear_env(env);
		ft_malloc(0, 1);
		exit(0);
	}
	else if (check_builts(data))
	{
		handle_builts(data);
		ft_lstclear_env(env);
		ft_malloc(0, 1);
		exit(0);
	}
}

void	exec(t_data *data)
{
	char	*path;
	char	**envp;

	if (!ft_strcmp("minishell", data->args[0]))
	{
		ft_putstr_fd(data->cmd, 2);
		ft_putendl_fd(": command not found", 2);
		ft_malloc(0, 1);
		ft_lstclear_env(env);
		exit(127);
	}
	path = NULL;
	envp = NULL;
	if (data && data->cmd)
		handle_execve(data, path, envp);
}

void	handle_process_execution(t_data *data)
{
	if (!check_builts(data))
	{
		if (data && data->cmd)
			exec(data);
		ft_lstclear_env(env);
		ft_malloc(0, 1);
		exit(0);
	}
	else
	{
		handle_builts(data);
		ft_lstclear_env(env);
		ft_malloc(0, 1);
		exit(0);
	}
}

void	process_pipe(t_data *data)
{
	ft_execute_multiple(data);
}
