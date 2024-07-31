/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 20:05:37 by mchihab           #+#    #+#             */
/*   Updated: 2024/07/31 18:08:15 by mchihab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_input(t_files *file)
{
	int	fd;

	while (file)
	{
		fd = open(file->delimiter, O_RDONLY, 0644);
		if (fd == -1)
		{
			ft_putstr_fd(my_strjoin("minishell: ", file->delimiter), 2);
			perror(" ");
			ft_putstr_fd("", 2);
			g_env->exit_status = 1;
			return (1);
		}
		if (file->next)
		{
			dup2(fd, 0);
			close(fd);
		}
		else
			file->index = fd;
		file = file->next;
	}
	return (0);
}

int	ft_output(t_files *file)
{
	int	fd;

	while (file)
	{
		fd = open(file->delimiter, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd == -1)
		{
			ft_putstr_fd(my_strjoin("minishell: ", file->delimiter), 2);
			perror(" ");
			ft_putstr_fd("", 2);
			g_env->exit_status = 1;
			return (1);
		}
		if (file->next)
		{
			dup2(fd, 1);
			close(fd);
		}
		else
			file->index = fd;
		file = file->next;
	}
	return (0);
}

int	ft_append_file(t_files *file)
{
	int	fd;

	while (file)
	{
		fd = open(file->delimiter, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd == -1)
		{
			ft_putstr_fd(my_strjoin("minishell: ", file->delimiter), 2);
			perror(" ");
			ft_putstr_fd("", 2);
			g_env->exit_status = 1;
			return (1);
		}
		if (file->next)
		{
			dup2(fd, 1);
			close(fd);
		}
		else
			file->index = fd;
		file = file->next;
	}
	return (0);
}

void	handle_child_redirections(t_data *data, int fds[])
{
	(void)fds;
	if (data)
	{
		if (data->redir_in)
			handle_input_redirection(data);
		if (data->redir_out)
			handle_output_redirection(data);
		if (data->append)
			handle_append_redirection(data);
		if(check_heredoc_two(data))
			handle_heredoc(data);
	}
	close(fds[1]);
}

void	handle_heredoc(t_data *data)
{
	int	fd;

	if (check_heredoc(data))
	{
		fd = open("/tmp/heredoc.txt", O_RDONLY, 777);
		if (fd == -1)
		{
			ft_putstr_fd(my_strjoin("minishell: ", "/tmp/heredoc.txt"), 2);
			perror(" ");
			g_env->exit_status = 1;
			ft_malloc(0, 1);
			ft_lstclear_env(g_env);
			exit(1);
		}
		if (data->last_file == 2)
			dup2(fd, 0);
		close(fd);
	}
}
