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
	int(pid), (status);
	while (data && data->next)
	{
		if (data && (data->cmd || data->heredoc))
			create_pipes(data);
		data = data->next;
	}
	pid = fork();
	if (!pid)
	{
		handle_process_redirections(data);
		if (data && (data->cmd || data->heredoc))
			handle_process_execution(data);
	}
	waitpid(pid, &status, 0);
	env->exit_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		env->exit_status = WTERMSIG(status) + 128;
}