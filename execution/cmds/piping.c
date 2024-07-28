/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 19:58:53 by mchihab           #+#    #+#             */
/*   Updated: 2024/07/28 18:06:19 by mchihab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	create_pipes(t_data *data)
{
	int	fds[2];
	int	pid;

	if (pipe(fds) == -1)
	{
		perror("pipe:");
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
	{
		close(fds[0]);
		dup2(fds[1], 1);
		handle_child_redirections(data, fds);
		handle_child_execution(data);
	}
	close(fds[1]);
	dup2(fds[0], 0);
	close(fds[0]);
}

void	ft_execute_multiple(t_data *data)
{
	int (pid), (status);
	while (data && data->next)
	{
		create_pipes(data);
		data = data->next;
	}
	(signal(SIGINT, SIG_IGN), signal(SIGQUIT, SIG_IGN));
	pid = fork();
	if (!pid)
	{
		handle_process_redirections(data);
		handle_process_execution(data);
	}
	waitpid(pid, &status, 0);
	g_env->exit_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		g_env->exit_status = WTERMSIG(status) + 128;
}
