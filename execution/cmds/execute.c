#include "../../minishell.h"

char	*get_path_two(char *cmd)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;
	t_envp	*tmp;
	char	*value;

	tmp = env;
	if (!cmd)
		return (NULL);
	if (!access(cmd, X_OK) || cmd[0] == '/')
		return (ft_strdup(cmd));
	value = my_get_env(tmp, "PATH");
	allpath = ft_split(value, ':');
	if (!allpath)
		return (NULL);
	i = -1;
	while (allpath[++i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, cmd);
		free(path_part);
		if (access(exec, X_OK) == 0)
		{
			ft_freed(allpath);
			free(value);
			return (exec);
		}
		free(exec);
	}
	if ((access(cmd, F_OK) == 0 && access(cmd, X_OK) != 0) && (cmd[0] == '/'
			|| cmd[ft_strlen(cmd) - 1] == '/' || (cmd[0] == '.'
				&& cmd[1] == '/')))
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		exit(126);
	}
	free(value);
	ft_freed(allpath);
	return (NULL);
}
void	handle_child_redirections(t_data *data, int fds[])
{
	t_files	*file;
	int		fd;

	if (data && data->redir_in)
	{
		if (ft_input(data->redir_in))
			exit(1);
		file = ft_lstlast_file(data->redir_in);
		dup2(file->index, 0);
		close(file->index);
	}
	if (data && data->redir_out)
	{
		if (ft_output(data->redir_out))
			exit(1);
		file = ft_lstlast_file(data->redir_out);
		dup2(file->index, 1);
		close(file->index);
	}
	if (data && data->append)
	{
		if (ft_append_file(data->append))
			exit(1);
		file = ft_lstlast_file(data->append);
		dup2(file->index, 1);
		close(file->index);
	}
	if (check_heredoc(data))
	{
		fd = open("/tmp/heredoc.txt", O_RDONLY, 0644);
		if (fd == -1)
		{
			ft_putstr_fd(my_strjoin("minishell: ", "/tmp/heredoc.txt"), 2);
			perror(" ");
			ft_putstr_fd("", 2);
			env->exit_status = 1;
			exit(1);
		}
		dup2(fd, 0);
		close(fd);
	}
	if (!data->cmd || !data->cmd[0])
		exit(127);
	close(fds[1]);
}
static bool	is_directory(char *path)
{
	int	fd;

	fd = open(path, __O_DIRECTORY);
	return (fd != -1);
}

void	handle_child_execution(t_data *data)
{
	if (!check_builts(data))
		exec(data);
	else
	{
		handle_builts(data);
		ft_lstclear_env(&env); // Free allocated resources
		ft_malloc(0, 1);
		exit(0);
	}
}

void	create_pipes(t_data *data)
{
	int	fds[2];
	int	pid;

	if (pipe(fds) == -1)
	{
		perror("pipe:");
		return ;
	}
	if ((pid = fork()) == -1)
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
void	exec(t_data *data)
{
	char	*path;
	char	**envp;

	if (!ft_strcmp("minishell", data->args[0]))
	{
		ft_putstr_fd(data->cmd, 2);
		ft_putendl_fd(": command not found", 2);
		return ;
	}
	path = get_path(data->cmd);
	envp = list_to_pointer();
	if (path)
	{
		if (is_directory(path))
		{
			free(path);
			ft_freed(envp);
			handle_directory_error(data->cmd);
		}
	}
	handle_execve(data, path, envp);
}
void	handle_process_redirections(t_data *data)
{
	t_files	*file;
	int		fd;

	if (data && data->redir_in)
	{
		if (ft_input(data->redir_in))
			exit(1);
		file = ft_lstlast_file(data->redir_in);
		dup2(file->index, 0);
		close(file->index);
	}
	if (data && data->redir_out)
	{
		if (ft_output(data->redir_out))
			exit(1);
		file = ft_lstlast_file(data->redir_out);
		dup2(file->index, 1);
		close(file->index);
	}
	if (data && data->append)
	{
		if (ft_append_file(data->append))
			exit(1);
		file = ft_lstlast_file(data->append);
		dup2(file->index, 1);
		close(file->index);
	}
	if (check_heredoc(data))
	{
		fd = open("/tmp/heredoc.txt", O_RDONLY, 0644);
		if (fd == -1)
		{
			ft_putstr_fd(my_strjoin("minishell: ", "/tmp/heredoc.txt"), 2);
			perror(" ");
			ft_putstr_fd("", 2);
			env->exit_status = 1;
			exit(1);
		}
		dup2(fd, 0);
		close(fd);
	}
	if (!data->cmd || !data->cmd[0])
		exit(127);
}

void	handle_process_execution(t_data *data)
{
	if (!check_builts(data))
	{
		exec(data);
		ft_malloc(0, 1);
		ft_lstclear_env(&env); // Free allocated resources
	}
	else
	{
		handle_builts(data);
		ft_lstclear_env(&env);
		ft_malloc(0, 1);
		exit(0);
	}
}

void	ft_execute_multiple(t_data *data)
{
	int pid, status;
	while (data && data->next)
	{
		create_pipes(data);
		data = data->next;
	}
	pid = fork();
	if (!pid)
	{
		handle_process_redirections(data);
		handle_process_execution(data);
	}
	else
	{
		waitpid(pid, &status, 0);
		env->exit_status = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			env->exit_status = WTERMSIG(status) + 128;
	}
}

// void check_shlvl(t_data *data)
// {

// }
void	process_pipe(t_data *data)
{
	if (data && !ft_strcmp(data->args[0], "./minishell"))
		inc_shell();
	// if(data && !ft_strcmp(data->args[0],"exit"))
	// 	dec_shell();
	ft_execute_multiple(data);
}
