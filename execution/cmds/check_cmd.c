/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 19:54:27 by mchihab           #+#    #+#             */
/*   Updated: 2024/07/28 18:06:19 by mchihab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_redir(t_data *data, t_files *file)
{
	if (data && data->redir_in)
	{
		if (ft_input(data->redir_in))
			return ;
		file = ft_lstlast_file(data->redir_in);
		if (data->last_file == 1)
			dup2(file->index, 0);
		close(file->index);
	}
	if (data && data->redir_out)
	{
		if (ft_output(data->redir_out))
			return ;
		file = ft_lstlast_file(data->redir_out);
		dup2(file->index, 1);
		close(file->index);
	}
	if (data && data->append)
	{
		if (ft_append_file(data->append))
			return ;
		file = ft_lstlast_file(data->append);
		dup2(file->index, 1);
		close(file->index);
	}
}

void	hide_inout(int a)
{
	if (!a)
	{
		dup2(0, 199);
		dup2(1, 200);
	}
	else
	{
		dup2(199, 0);
		dup2(200, 1);
	}
}

void	check_empty_cmd_two(t_data *data)
{
	if (data && data->cmd && data->cmd[0] == '\0')
	{
		ft_putendl_fd("command '' not found", 2);
		return ;
	}
}

void	process_cmd(t_data *data)
{
	t_files	*file;

	int (status), (flag);
	file = NULL;
	flag = 0;
	g_env->signal_heredoc = 0;
	hide_inout(0);
	if (data && check_heredoc_two(data))
	{
		heredoc_mult(data);
		hide_inout(1);
	}
	if (data && !data->next && check_builts(data) && !g_env->signal_heredoc)
	{
		(execute_single_cmd(data), hide_inout(1));
		flag = 1;
	}
	else if (data && !flag && !g_env->signal_heredoc)
	{
		(process_pipe(data), hide_inout(1));
		while (waitpid(-1, &status, 0) != -1)
			;
	}
	else
		check_redir(data, file);
}
