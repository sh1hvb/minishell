#include "../../minishell.h"

static int	ft_lstsize_data(t_data *lst)
{
	int	count;

	if (!lst)
		return (0);
	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}


static char	*get_path(char **cmd, t_envp *env)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;
	// char	**s_cmd;

    t_envp *tmp = env;

	i = -1;
	if (!access(cmd[0], X_OK))
		return (cmd[0]);
	allpath = ft_split(my_get_env(tmp,"PATH" ), ':');
	if (!allpath)
		return (NULL);
	while (allpath[++i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, cmd[0]);
		// free(path_part);
		if (access(exec, X_OK) == 0)
        {
			return (exec);

        }
		// free(exec);
	}
	return (cmd[0]);
}
static void	exec(char **cmd, t_envp *env , char *envp[])
{
	// char	**s_cmd;
	char	*path;
	int	fds[2];
	int	pid;

	path = get_path(cmd, env);
    dprintf(2,"%s\n", path);
	if (pipe(fds) == -1)
		perror("pipe:");
	pid = fork();
	if (pid == -1)
		perror("fork");
	if (!pid)
	{
        close(fds[0]);
		// dup2(fds[1], 1);
		if (execve(path, cmd, envp) == -1)
        {
            dprintf(2,"not found");
            exit(127);


        }
	}
	else
	{
		close(fds[1]);
		// dup2(fds[0], 0);
        wait(NULL);
	}
}
void	add_pipe(t_data *data, t_envp *env, char *envp[])
{
	int	fds[2];
	int	pid;

	if (pipe(fds) == -1)
		perror("pipe:");
	pid = fork();
	if (pid == -1)
		perror("fork");
	if (!pid)
	{
		close(fds[0]);
		dup2(fds[1], 1);
        if(!check_builts(data))
		    exec(data->args, env, envp);
        else
            handle_builts(data);
	}
	else
	{
		close(fds[1]);
		dup2(fds[0], 0);
        // wait(NULL);

	}
}
// void	create_pipes_and_execute(int ac, char *av[], char *env[], int fd_out)
// {
// 	int i, (pid);
// 	if (ft_strcmp(av[1], "here_doc") == 0)
// 		i = 3;
// 	else
// 		i = 2;
// 	while (i < ac - 2)
// 		add_pipe(av[i++], env);
// 	pid = fork();
// 	if (!pid)
// 	{
// 		dup2(fd_out, 1);
// 		exec(av[ac - 2], env);
// 	}
// 	close(fd_out);
// }
void check_cmd(t_data *data, t_envp *env, char *envp[])
{
    int i = 0;
    if(!data->next)
    {
        if(!check_builts(data))
		    exec(data->args, env ,envp);
        else if(check_builts(data))
            handle_builts(data);
        else
            printf("cmd");
    }
    else
    {
        i = ft_lstsize_data(data);   
        while(i-- > 1)
        {
            add_pipe(data,e/nv,envp);
            // printf("%s\n",data->args[0]);
            data = data->next;
        }
    }
}