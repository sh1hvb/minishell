#include "../../minishell.h"

 int	ft_lstsize_file(t_files *lst)
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

static char	*get_path(char *cmd)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;
    t_envp *tmp = env;

	if (!cmd)
		return NULL;
	if (!access(cmd, X_OK) || cmd[0] == '/')
		return (ft_strdup(cmd));
	char *value = my_get_env(tmp, "PATH");
	allpath = ft_split(value, ':');
	if (!allpath)
		return (NULL);
	i = -1;
	while (allpath[++i] )
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, cmd);
		free(path_part);

		if (access(exec, X_OK) == 0)
        {
			// ft_freed(allpath);
			free(value);
			return (exec);
        }
		free(exec);
	}
	if ((access(cmd , F_OK) == 0 && access(cmd , X_OK) != 0) && (cmd[0] == '/' || cmd[ft_strlen(cmd) - 1] == '/' ||(cmd[0] == '.' && cmd[1] == '/')))
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		exit (126);
	}
	free(value);
	ft_freed(allpath);
	return (NULL);
}

void create_pipes(t_data *data)
{
	t_files *file;

	int (pid) ,fds[2] ,flag;
	flag = 0;
	if(pipe(fds) == -1 )
	{
		perror("pipe :");
		return ;
	}
	if(data && check_heredoc(data))
		heredoc_mult(data,fds);
	
	if((pid = fork() )== -1)
		perror("fork");
	if(!pid)
	{
		if(data && data->redir_in)
		{
			if (ft_input(data->redir_in))
				exit (1);
			file = ft_lstlast_file(data->redir_in);
			dup2(file->index, 0);
			close(file->index);
		}
		if(data && data->redir_out)
		{
			if (ft_output(data->redir_out))
				exit (1);
			file = ft_lstlast_file(data->redir_out);
			dup2(file->index, 1);
			close(file->index);
			flag = 1;
		}
		if(data && data->append)
		{
			if (ft_append_file(data->append))
				exit (1);
			file = ft_lstlast_file(data->append);
			dup2(file->index, 0);
			close(file->index);
		}
		if ((data && !data->cmd) || !data->cmd[0])
				exit (127);
		close(fds[0]);
		if (!flag)
			dup2(fds[1], 1);
		else
			close(fds[1]);
		
		 if(!check_builts(data))
			exec(data);
		else if(check_builts(data))
		{
			handle_builts(data);
			exit(0);
		}
	}
	close(fds[1]);
	dup2(fds[0], 0);
	close(fds[0]);
}

void exec(t_data *data)
{
	char *path;
	char **envp;
	if(!ft_strcmp("minishell", data->args[0]))
	{
		ft_putstr_fd( data->cmd ,2);
		ft_putendl_fd(" : command not found",2);
		return ;
	}
	path = get_path(data->cmd);
	envp = list_to_pointer();
	if (path)
	{
		int fd = open(path, __O_DIRECTORY);
		if (fd != -1)
		{
			free(path);
			ft_freed(envp);
			ft_putstr_fd("minishell: ",2);
			ft_putstr_fd(data->cmd, 2);
			ft_putstr_fd(": Is a directory\n", 2);
			exit (126);
		}
	}
	if(execve(path , data->args ,envp) == -1 || access(path , X_OK | F_OK)!= 0)
	{
		free(path);
		ft_freed(envp);
		ft_putstr_fd( data->cmd ,2);
		perror(" : command not found");
		exit (127);
	}
}
void ft_execute_multiple(t_data *data)
{
	int (pid),status;
	t_files *file;
	
	while(data && data->next)
	{
		create_pipes(data);
		data = data->next;
	}
	pid = fork();
	if(!pid)
	{
		if(data && data->redir_in)
		{
			if (ft_input(data->redir_in))
				exit (1);
			file = ft_lstlast_file(data->redir_in);
			dup2(file->index, 0);
			close(file->index);
		}
		if(data && data->redir_out)
		{
			if (ft_output(data->redir_out))
				exit (1);
			file = ft_lstlast_file(data->redir_out);
			dup2(file->index, 1);
			close(file->index);
		}
		if(data && data->append)
		{
			if (ft_append_file(data->append))
				exit (1);
			file = ft_lstlast_file(data->append);
			dup2(file->index, 0);
			close(file->index);
		}
		if ((data && !data->cmd) || !data->cmd[0])
		{
				exit (127);

		}
		else if(!check_builts(data))
		{
			exec(data);
			while (waitpid(pid, &status, 0) != -1);
			env->exit_status = status;
		}
		else if(check_builts(data))
		{
			handle_builts(data);
			exit (0);
		}
	}

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
	char *path;
	char **envp;
	int	index;
	if(data && data->heredoc)
		heredoc(data);
	if(data && data->cmd)
	{
		if(!ft_strcmp("minishell", data->args[0]))
		{
			ft_putstr_fd(data->cmd ,2);
			ft_putendl_fd(": command not found", 2);
			return ;
		}
	}
	path = get_path(data->cmd);
	envp = list_to_pointer();
	if (path)
	{
		if (data->cmd[0] == '/' && access(path, X_OK) != 0)
			{
				ft_putstr_fd("minishell: ",2);
				ft_putstr_fd(data->cmd, 2);
				ft_putstr_fd(": No such file or directory\n", 2);
				exit (127);
			}
		int fd = open(path, __O_DIRECTORY);
		if (fd != -1)
		{
			free(path);
			ft_freed(envp);
			ft_putstr_fd("minishell: ",2);
			ft_putstr_fd(data->cmd, 2);
			if (data->cmd[0] == '/' || data->cmd[ft_strlen(data->cmd) - 1] == '/' ||( data->cmd[0] == '.' && data->cmd[1] == '/'))
			{
				ft_putstr_fd(": Is a directory\n", 2);
				exit (126);
			}
			
			else
			{
				ft_putstr_fd(": command not found\n", 2);
				exit (127);
			}
		}
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
	if((data && !data->cmd) || !data->cmd[0])
		exit (127);
	if(execve(path , data->args ,envp) == -1 || access(path , X_OK & F_OK)!= 0)
	{
		
		ft_putstr_fd( data->cmd ,2);
		if (access(path , X_OK & F_OK)!= 0 && (data->cmd[0] == '/' || data->cmd[ft_strlen(data->cmd) - 1] == '/' ||( data->cmd[0] == '.' && data->cmd[1] == '/')))
			ft_putstr_fd(": No such file or directory\n", 2);
		else
			ft_putendl_fd(" : command not found",2);
		exit (127);
	}
}
void execute_single_cmd(t_data *data)
{
	int (pid),(status), index;
	if(data && (data->redir_in || data->redir_out || data->append || data->heredoc))
	{	
		if(data->append)
			if (ft_append_file(data->append))
				return ;
		if(data->redir_in)
			if (ft_input(data->redir_in))
				return ;
		if(data->redir_out)
		{
			if (ft_output(data->redir_out))
				return ;
		}
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

	if(data->cmd)
	{	
		if(data && !ft_strcmp(data->args[0],"./minishell"))
		{
			inc_shell();
		}
	}
	if(check_builts(data))
		handle_builts(data);
	else
	{
		pid = fork();
		if(!pid)
				execute(data);
		while (waitpid(pid, &status, 0) != -1)
		{
			if (WIFEXITED(status))
			{
				status = WEXITSTATUS(status);
				env->exit_status = status;
				if (status == 127 || status == 126 || status == 1 || status == 0)
				{
					break ;
				}
			}
		};
	}
	if(ft_lstlast_file(data->redir_in) && ft_lstlast_file(data->redir_in)->index)
		close(ft_lstlast_file(data->redir_in)->index);
	if (ft_lstlast_file(data->redir_out) && ft_lstlast_file(data->redir_out)->index)
		close(ft_lstlast_file(data->redir_out)->index);
	if(ft_lstlast_file(data->heredoc) && ft_lstlast_file(data->heredoc)->index)
		close(ft_lstlast_file(data->heredoc)->index);
}
