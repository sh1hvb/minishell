#include "../../minishell.h"

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
			exit(127);
	}
	close(fds[1]);
}

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
		exec(data);
		ft_lstclear_env(env);
		ft_malloc(0, 1);
	}
	else if (check_builts(data))
	{
		handle_builts(data);
		ft_lstclear_env(env);
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
	path = NULL;
	envp = NULL;
	
	handle_execve(data, path, envp);
}

void	handle_process_redirections(t_data *data)
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
			exit(127);
	}
}

void	handle_process_execution(t_data *data)
{
	if (!check_builts(data))
	{
		
		exec(data);
	}
	else
	{
		handle_builts(data);
		ft_lstclear_env(env);
		ft_malloc(0, 1);
		exit(0);
	}
}

void	ft_execute_multiple(t_data *data)
{
	int (pid), (status);
	int (pid), (status);
	while (data && data->next)
	{
		if (data->cmd)
			create_pipes(data);
		data = data->next;
	}
	pid = fork();
	if (!pid)
	{
		handle_process_redirections(data);
		if (data->cmd)
			handle_process_execution(data);
	}
	waitpid(pid, &status, 0);
	env->exit_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		env->exit_status = WTERMSIG(status) + 128;
}

void	process_pipe(t_data *data)
{
	ft_execute_multiple(data);
}
