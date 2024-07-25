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

void	handle_input_redirection(t_data *data)
{
	t_files	*file;

	if (ft_input(data->redir_in))
		exit(1);
	file = ft_lstlast_file(data->redir_in);
	dup2(file->index, 0);
	close(file->index);
}

void	handle_output_redirection(t_data *data)
{
	t_files	*file;

	if (ft_output(data->redir_out))
		exit(1);
	file = ft_lstlast_file(data->redir_out);
	dup2(file->index, 1);
	close(file->index);
}

void	handle_append_redirection(t_data *data)
{
	t_files	*file;

	if (ft_append_file(data->append))
		exit(1);
	file = ft_lstlast_file(data->append);
	dup2(file->index, 1);
	close(file->index);
}

void	handle_heredoc(t_data *data)
{
	int	fd;

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
// int	ft_heredoc(t_files *file)
// {
// 	int	fd;
// 	char *path ="/tmp";
// 	int i = 0;
// 	char *joined;
// 	char *s;
// 	while (file && i <=16)
// 	{
// 		i++;
// 		s = ft_itoa(i);
// 		joined = ft_strjoin(path,s);
// 		fd = open(joined, O_CREAT | O_RDWR | O_APPEND, 0644);
// 		if (fd == -1)
// 		{
// 			ft_putstr_fd(my_strjoin("minishell: ", file->delimiter), 2);
// 			perror(" ");
// 			ft_putstr_fd("", 2);
// 			return (1);
// 		}
// 		free(joined);
// 		free(s);
// 		if (file->next)
// 			close(fd);
// 		else
// 			file->index = fd;
// 		file = file->next;
// 	}
// 	return (0);
// }
// void	ft_append(t_files *file)
// {
// 	int	fd;

// 	while (file && file->next)
// 	{
// 		open(file->delimiter, O_WRONLY, O_APPEND, 0644);
// 		file = file->next;
// 	}
// 	fd = open(file->delimiter, O_WRONLY, O_APPEND, 0644);
// 	file->index = fd;
// }
