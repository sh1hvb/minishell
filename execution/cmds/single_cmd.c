#include "../../minishell.h"
#include <errno.h>


// void	handle_command_not_found(t_data *data)
// {
// 	if (data && data->cmd && !ft_strcmp("minishell", data->args[0]))
// 	{
// 		ft_putstr_fd(data->cmd, 2);
// 		ft_putendl_fd(": command not found", 2);
// 		return ;
// 	}
// }

// void	handle_path_access(t_data *data, char *path, char **envp)
// {
// 	if (!data->cmd[0])
// 		exit(127);
// 	if (data->cmd[0] == '/' && access(path, X_OK) != 0)
// 	{
// 		ft_putstr_fd("minishell: ", 2);
// 		ft_putstr_fd(data->cmd, 2);
// 		ft_putstr_fd(": No such file or directory\n", 2);
// 		exit(127);
// 	}

// 	int fd = open(path, __O_DIRECTORY);
// 	if (fd != -1)
// 	{
// 		free(path);
// 		ft_freed(envp);
// 		ft_putstr_fd("minishell: ", 2);
// 		ft_putstr_fd(data->cmd, 2);
// 		if (data->cmd[0] == '/' || data->cmd[ft_strlen(data->cmd) - 1] == '/'
// 			|| (data->cmd[0] == '.' && data->cmd[1] == '/'))
// 		{
// 			ft_putstr_fd(": Is a directory\n", 2);
// 			exit(126);
// 		}
// 		else
// 		{
// 			ft_putstr_fd(": command not found\n", 2);
// 			exit(127);
// 		}
// 	}
// }

void	handle_redirections(t_data *data)
{
	int index;
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

void	handle_invalid_command(void)
{
	ft_putendl_fd("Invalid command", 2);
	ft_lstclear_env(env);
	ft_malloc(0, 1);
	exit(127);
}

void	handle_access_error(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	if (errno == EACCES)
	{
		ft_putendl_fd(": Permission denied", 2);
		ft_lstclear_env(env);
			ft_malloc(0, 1);
		exit(126);
	}
	else if (errno == ENOENT && (cmd[0] == '/'
			|| cmd[ft_strlen(cmd) - 1] == '/' || (cmd[0] == '.'
				&& cmd[1] == '/')))
	{
		ft_putendl_fd(": No such file or directory", 2);
		ft_lstclear_env(env);
		ft_malloc(0, 1);
		exit(126);
	}
	else
		ft_putendl_fd(": command not found", 2);
	ft_lstclear_env(env);
	ft_malloc(0, 1);
	exit(127);
}

void	handle_execve_error(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	if (errno == EACCES)
	{
		ft_putendl_fd(": Permission denied", 2);
			ft_lstclear_env(env);
			ft_malloc(0, 1);
		exit(126);
	}
	else if (errno == ENOENT && (cmd[0] == '/'
			|| cmd[ft_strlen(cmd) - 1] == '/' || (cmd[0] == '.'
				&& cmd[1] == '/')))
	{
		ft_putendl_fd(": No such file or directory", 2);
		ft_malloc(0, 1);
		ft_lstclear_env(env);
		exit(126);
	}
	else
	{
		ft_lstclear_env(env);
		ft_putendl_fd(": Command not found", 2);
		ft_malloc(0, 1);
		exit(127);
	}
}

void	handle_execve(t_data *data, char *path, char **envp)
{
	if (!data || !data->cmd || !data->cmd[0])
		handle_invalid_command();
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

// void	execute(t_data *data)
// {
// 	char *path;
// 	char **envp;

// 	handle_command_not_found(data);

// 	path = get_path(data->cmd);
// 	if (path)
// 	{
// 		envp = list_to_pointer();
// 		handle_path_access(data, path, envp);
// 		handle_redirections(data);
// 		handle_execve(data, path, envp);
// 	}
// 	else
// 	{
// 		ft_putstr_fd("minishell: ", 2);
// 		ft_putstr_fd(data->cmd, 2);

// 		if (access(data->cmd, X_OK & F_OK) != 0 && (data->cmd[0] == '/'
// 				|| data->cmd[ft_strlen(data->cmd) - 1] == '/'
// 				|| (data->cmd[0] == '.' && data->cmd[1] == '/')))
// 			ft_putstr_fd(": No such file or directory\n", 2);
// 		else
// 			ft_putstr_fd(" : command not found\n", 2);
// 		free(path);
// 		ft_malloc(0, 1);
// 		ft_lstclear_env(env);
// 		exit(127);
// 	}
// }

// void	handle_heredoc(t_data *data)
// {
// 	if (data && check_heredoc(data))
// 		heredoc(data);
// }

int	handle_file_redirections(t_data *data)
{
	if (data->append && ft_append_file(data->append))
		return (1);
	if (data->redir_in && ft_input(data->redir_in))
		return (1);
	if (data->redir_out && ft_output(data->redir_out))
		return (1);
	return (0);
}

void	setup_redirections(t_data *data)
{
	int index;
	if (ft_lstlast_file(data->append))
	{
		index = ft_lstlast_file(data->append)->index;
		dup2(index, 1);
		close(index);
	}
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

void	close_file_descriptors(t_data *data)
{
	if (ft_lstlast_file(data->redir_in)
		&& ft_lstlast_file(data->redir_in)->index)
		close(ft_lstlast_file(data->redir_in)->index);
	if (ft_lstlast_file(data->redir_out)
		&& ft_lstlast_file(data->redir_out)->index)
		close(ft_lstlast_file(data->redir_out)->index);
	if (ft_lstlast_file(data->heredoc)
		&& ft_lstlast_file(data->heredoc)->index)
		close(ft_lstlast_file(data->heredoc)->index);
}

void	execute_built_in_or_fork(t_data *data)
{
	int pid;
	if (check_builts(data))
	{
		handle_builts(data);
		return ;
	}
	else if (!data || !data->cmd || !data->cmd[0])
		return ;
	else
	{
		pid = fork();
		if (!pid)
		{
			if (!data->cmd)
				exit(0);
			exec(data);
			ft_malloc(0, 1);
			ft_lstclear_env(env);
		}
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
