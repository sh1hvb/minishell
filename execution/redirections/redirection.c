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
			env->exit_status = 1;
			return (1);
		}
		if (file->next)
			close(fd);
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
			env->exit_status = 1;
			return (1);
		}
		if (file->next)
			close(fd);
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
			env->exit_status = 1;
			return (1);
		}
		if (file->next)
			close(fd);
		else
			file->index = fd;
		file = file->next;
	}
	return (0);
}
void	handle_child_redirections(t_data *data, int fds[])
{
	if (data)
	{
		if (data->redir_in)
			handle_input_redirection(data);
		if (data->redir_out)
			handle_output_redirection(data);
		if (data->append)
			handle_append_redirection(data);
		handle_heredoc(data);
		if (!data->cmd || !data->cmd[0])
		{
			ft_lstclear_env(env);
			ft_malloc(0, 1);
			exit(127);
		}
	}
	close(fds[1]);
}

void	handle_heredoc(t_data *data)
{
	int fd;

	if (check_heredoc(data))
	{
		fd = open("/tmp/heredoc.txt", O_RDONLY, 0644);
		if (fd == -1)
		{
			ft_putstr_fd(my_strjoin("minishell: ", "/tmp/heredoc.txt"), 2);
			perror(" ");
			env->exit_status = 1;
			exit(1);
		}
		dup2(fd, 0);
		close(fd);
	}
}