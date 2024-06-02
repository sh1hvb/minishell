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
void inc_shell() {
    int tmp;
    t_envp *tmpenv = env;

    while (tmpenv) {
        if (!ft_strcmp(tmpenv->key, "SHLVL")) {
            tmp = ft_atoi(tmpenv->value) + 1;
            free(tmpenv->value);
            tmpenv->value = ft_itoa(tmp);
			break;
        }
        tmpenv = tmpenv->next;
    }
}

static void	exec_cmd(char **cmd, t_envp *env, char *envp[])
{
	char	*path;
	char **env_tmp;
	env_tmp =NULL;
	path = get_path(cmd, env);
	if(!ft_strcmp("minishell", cmd[0]))
	{
		perror("cmd not found");
		return ;
	}(void)envp;;
	env_tmp = list_to_pointer();
	if(!ft_strcmp("./minishell", cmd[0]))
	{
		inc_shell();
	}
	if (execve(path, cmd, env_tmp) == -1)
    {
        perror("execve");
        return ;
    }
}

void	add_pipe(t_data *data, t_envp *env, char *envp[])
{
	int	fds[2];
	int	pid;
	// int (status),(exit_status) = 0;


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
		{
			if(data && !ft_strcmp(data->cmd, "exit"))
					data = data->next;
			else
            	handle_builts(data);
			close(fds[1]);
			exit (0);
		}
		close(fds[1]);
	}
	close(fds[1]);
	dup2(fds[0], 0);
	close(fds[0]);
}
char **list_to_pointer()
{
	int i = 0;
	char **arr = NULL;
	char *tmp;
	tmp = NULL;
	int size = ft_lstsize_env(env);
	arr = malloc((size + 1) * sizeof(char *));
	if(!arr)
		return NULL;
	while(env)
	{
		tmp = ft_strjoin(env->key,"=");
		arr[i] = ft_strjoin(tmp,env->value);
		// free(tmp);
		i++;
		env = env->next;
	}
	arr[i] = NULL;
	return arr;
}
void check_cmd(t_data *data, t_envp *env, char *envp[])
{

	dup2(0, 3);
	int (status), (exit_status);
	if(data && !ft_strcmp(data->cmd, "exit") && !data->next)
		ft_exit(data);
	else
	{
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
					{
						if(data && !ft_strcmp(data->cmd, "exit"))
							data = data->next;
						else
							handle_builts(data);
					}
				}
				while (waitpid(pid, &status, 0) != -1)
				{
					if (WIFEXITED(status))
					{
						exit_status = WEXITSTATUS(status);
						if (exit_status == 127 || exit_status == 1 || exit_status == 0)
							break ;
					}
				}
			}
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
	// while (waitpid(-1, &status, 0) != -1)
	// {
	// 	if (WEXITSTATUS(status) == 127 || WEXITSTATUS(status) == 1 || WEXITSTATUS(status) == 0)
	// 		exit(WEXITSTATUS(status));
	// };