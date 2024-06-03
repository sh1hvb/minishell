#include "../../minishell.h"

static int	ft_lstsize_file(t_files *lst)
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

static char	*get_path(char **cmd)
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
	return (cmd[0]);
}

void create_pipes(t_data *data)
{
	t_files *file;
	int pid;
	int fds[2];
	if(pipe(fds) == -1 )
	{
		perror("pipe :");
	}
	pid = fork();
	if(!pid)
	{
		if(data && data->redir_in)
		{
			ft_input(data->redir_in);
			file = ft_lstlast_file(data->redir_in);
			dup2(file->index, 0);
		}
		close(fds[0]);
		dup2(fds[1], 1);
		exec(data);
	}
	else
	{
		close(fds[1]);
		dup2(fds[0], 0);
	}
}
void exec(t_data *data)
{
	char *path;
	char **envp;

	if(!ft_strcmp("minishell", data->args[0]))
	{
		perror("cmd not found");
		return ;
	}
	path = get_path(data->args);
	envp = list_to_pointer();
	if(execve(path , data->args ,envp) == -1)
	{
		perror("minishell : cmd not found");
		return ;
	}
}
void ft_execute_multiple(t_data *data)
{
	int (pid), (status), (exit_status) ;
	t_files *file;
	while(data && data->next)
	{
		create_pipes(data);
		data = data->next;
	}
	pid = fork();
	if(!pid)
	{
		if(data && data->redir_out)
		{
			ft_input(data->redir_out);
			file = ft_lstlast_file(data->redir_out);
			dup2(file->index, 1);
		}
		if(check_builts(data))
			handle_builts(data);
		else
			exec(data);
	}
	else
	{
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
	// }
}
void process_pipe(t_data *data)
{
	if(data && !ft_strcmp(data->args[0],"./minishell"))
		inc_shell();
	ft_execute_multiple(data);
}
t_files	*ft_lstlast_file(t_files *lst)
{
	int	last;

	last = ft_lstsize_file(lst);
	while (last-- > 1)
		lst = lst->next;
	return (lst);
}
void execute(t_data *data)
{
	char * path;
	char **envp;
	int	index;

	if(!ft_strcmp("minishell", data->args[0]))
	{
		perror("cmd not found");
		return ;
	}
	path = get_path(data->args);
	envp = list_to_pointer();
	if (ft_lstlast_file(data->redir_out))
	{
		index = ft_lstlast_file(data->redir_out)->index;
		dup2(index, 1);
	}
	if (ft_lstlast_file(data->redir_in))
	{
		index = ft_lstlast_file(data->redir_in)->index;
		dup2(index, 0);
	}
	if(execve(path , data->args ,envp) == -1)
	{
		perror("minishell : cmd not found");
		return ;
	}
}
void execute_single_cmd(t_data *data)
{
	int pid;

	if(data && (data->redir_in || data->redir_out || data->append))
	{	
		if(data->redir_in)
			ft_input(data->redir_in);
		if(data->redir_out)
			ft_output(data->redir_out);
	}
	if(check_builts(data))
		handle_builts(data);
	else
	{	
		pid = fork();
		if(!pid)
			execute(data);
		wait(&pid);
	}
	if(ft_lstlast_file(data->redir_in) && ft_lstlast_file(data->redir_in)->index)
		close(ft_lstlast_file(data->redir_in)->index);
	if (ft_lstlast_file(data->redir_out) && ft_lstlast_file(data->redir_out)->index)
		close(ft_lstlast_file(data->redir_out)->index);
}