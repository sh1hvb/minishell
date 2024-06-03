#include "../../minishell.h"

void	ft_input(t_files *file)
{
	int	fd;

	while (file)
	{
		fd = open(file->delimiter, O_RDONLY, 0644);
		if (fd == -1)
		{
			ft_putstr_fd(my_strjoin("minishell: ", file->delimiter), 2);
			perror("");
			ft_putstr_fd("", 2);
			return ;
		}
		if (file->next)
			close(fd); 
		else
			file->index = fd;
		file = file->next;
	}
	
}

void	ft_output(t_files *file)
{
	int	fd;

	while (file && file->next)
	{
		fd = open(file->delimiter, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		close(fd); 
		file = file->next;
	}
	fd = open(file->delimiter, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	file->index = fd;
}

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
