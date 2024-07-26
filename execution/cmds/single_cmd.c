#include "../../minishell.h"

void	handle_redirections(t_data *data)
{
	int	index;

	if (ft_lstlast_file(data->redir_out))
	{
		index = ft_lstlast_file(data->redir_out)->index;
		dup2(index, 1);
		close(index);
	}
	if (ft_lstlast_file(data->redir_in))
	{
		index = ft_lstlast_file(data->redir_in)->index;
		dup2(index, 0);
		close(index);
	}
}

void	handle_execve(t_data *data, char *path, char **envp)
{
	path = get_path(data->cmd);
	if (path)
	{
		if (is_directory(path))
		{
			free(path);
			handle_directory_error(data->cmd);
		}
	}
	else if (access(path, X_OK) != 0)
	{
		free(path);
		handle_access_error(data->cmd);
	}
	envp = list_to_pointer();
	if (execve(path, data->args, envp) == -1)
	{
		free(path);
		ft_freed(envp);
		handle_execve_error(data->cmd);
	}
}

void	execute_built_in_or_fork(t_data *data)
{
	if (check_builts(data))
	{
		handle_builts(data);
		return ;
	}
}

void	execute_single_cmd(t_data *data)
{
	if (!data)
		return ;
	if (data->redir_in || data->redir_out || data->append || data->heredoc)
	{
		if (handle_file_redirections(data))
			return ;
		setup_redirections(data);
	}
	execute_built_in_or_fork(data);
	close_file_descriptors(data);
}
