#include "../../minishell.h"

static char	*get_path(char **cmd, t_envp *env)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;
    t_envp *tmp = env;

	if (!cmd)
		return NULL;
	if (!access(cmd[0], X_OK))
		return (cmd[0]);

	allpath = ft_split(my_get_env(tmp, "PATH"), ':');
	if (!allpath)
		return (NULL);

	for (i = 0; allpath[i]; i++)
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, cmd[0]);
		// free(path_part);

		if (access(exec, X_OK) == 0)
        {
			// free(allpath);
			return (exec);
        }
		free(exec);
	}
	// ft_freed(allpath);
	return (exec);
}

static void	exec_cmd(char **cmd, t_envp *env, char *envp[])
{
	char	*path;

	path = get_path(cmd, env);
	if (execve(path, cmd, envp) == -1)
    {
        perror("execve");
        return ;
    }
}

static void	exec_cmd2(char **cmd, t_envp *env, char *envp[])
{
	char	*path;

	path = get_path(cmd, env);
	if (execve(path, cmd, envp) == -1)
    {
        perror("execve");
        return ;
    }
}

void	add_pipe(t_data *data, t_envp *env, char *envp[])
{
	int	fds[2];
	int	pid;

	if (pipe(fds) == -1)
	{
		perror("pipe");
		return;
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return;
	}

	if (pid == 0)
	{
		close(fds[0]);
		dup2(fds[1], 1);
        if (!check_builts(data))
		    exec_cmd(data->args, env, envp);
        else
            handle_builts(data);
	}
	close(fds[1]);
	dup2(fds[0], 0);
	close(fds[0]);
	
}

void check_cmd(t_data *data, t_envp *env, char *envp[])
{
	int	status;

	dup2(0, 3);
    while (data && data->next)
    {
        add_pipe(data, env, envp);
        data = data->next;
    }
	if (data)
	{
		int pid = fork();
		if(!pid)
		{
			if (!check_builts(data))
		    	exec_cmd2(data->args, env, envp);
        	else
            	handle_builts(data);
		}
		while (waitpid(-1, &status, 0) != -1)
		{
			if (WEXITSTATUS(status) == 127 || WEXITSTATUS(status) == 1)
				exit(WEXITSTATUS(status));
		};
	}
	dup2(3, 0);
}
// while (i < ac - 2)
// 		add_pipe(av[i++], env);
// 	pid = fork();
// 	if (!pid)
// 	{
// 		dup2(fd_out, 1);
// 		exec(av[ac - 2], env);
// 	}
// 	id = fork();
// 	if (!id)
// 		close(fd_out);
// 	else
// 		while (waitpid(-1, &status, 0) != -1)
// 		{
// 			if (WEXITSTATUS(status) == 127 || WEXITSTATUS(status) == 1)
// 				exit(WEXITSTATUS(status));
// 		};