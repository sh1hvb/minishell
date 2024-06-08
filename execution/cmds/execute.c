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

static char	*get_path(char *cmd)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;
    t_envp *tmp = env;

	if (!cmd)
		return NULL;
	if (!access(cmd, X_OK))
		return (cmd);
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
	free(value);
	ft_freed(allpath);
	return (NULL);
}

void create_pipes(t_data *data)
{
	t_files *file;
	int pid;
	int fds[2];
	int flag;

	flag = 0;
	
	if(pipe(fds) == -1 )
	{
		perror("pipe :");
		return ;
	}
	if(data && data->heredoc)
		heredoc_mult(data,fds);
	pid = fork();
	if(!pid)
	{
		if(data && data->redir_in)
		{
			ft_input(data->redir_in);
			file = ft_lstlast_file(data->redir_in);
			dup2(file->index, 0);
			close(file->index);
		}
	
		if(data && data->redir_out)
		{
			ft_output(data->redir_out);
			file = ft_lstlast_file(data->redir_out);
			dup2(file->index, 1);
			close(file->index);
			flag = 1;
		}
		
		if (data && !data->cmd)
		{
			// if(execve(NULL , NULL, NULL) == -1)
				exit (127);
		}
		close(fds[0]);
		if (!flag)
			dup2(fds[1], 1);
		else
			close(fds[1]);
		if(check_builts(data))
		{
			handle_builts(data);
			exit(0);
		}
		else if(!check_builts(data))
			exec(data);
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
		ft_putendl_fd(" : cmd not found",2);
		return ;
	}
	path = get_path(data->cmd);
	envp = list_to_pointer();
	if(execve(path , data->args ,envp) == -1 || access(path , X_OK | F_OK)!= 0)
	{
		free(path);
		ft_freed(envp);
		ft_putstr_fd( data->cmd ,2);
		ft_putendl_fd(" : cmd not found",2);
		exit (127);
	}
}
void ft_execute_multiple(t_data *data)
{
	int (pid);
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
			ft_input(data->redir_in);
			file = ft_lstlast_file(data->redir_in);
			dup2(file->index, 0);
			close(file->index);
		}
		if(data && data->redir_out)
		{
			ft_output(data->redir_out);
			file = ft_lstlast_file(data->redir_out);
			dup2(file->index, 1);
			close(file->index);
		}
		if (data && !data->cmd)
		{
				exit (127);
		}
		else if(check_builts(data))
			handle_builts(data);
		else if(!check_builts(data))
			exec(data);
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
	char * path;
	char **envp;
	int	index;
	if(data && data->heredoc)
		heredoc(data);
	if(data && data->cmd)
	{if(!ft_strcmp("minishell", data->args[0]))
	{
		ft_putstr_fd(data->cmd ,2);
		ft_putendl_fd(": cmd not found",2);
		return ;
	}}
	path = get_path(data->cmd);
	envp = list_to_pointer();
	if (ft_lstlast_file(data->redir_out))
	{
		index = ft_lstlast_file(data->redir_out)->index;
		dup2(index, 1);
		close(index);
	}
	if (ft_lstlast_file(data->redir_in))
	{
		index = ft_lstlast_file(data->redir_in)->index;
		dup2(index, 1);
		close(index);
	}
	
	if(execve(path , data->args ,envp) == -1 || access(path , X_OK & F_OK)!= 0)
	{
		ft_freed(envp);
		free(path);
		ft_putstr_fd( data->cmd ,2);
		ft_putendl_fd(" : cmd not found",2);
		exit (127);
	}
}
void execute_single_cmd(t_data *data)
{
	int pid;
	int status;
	// if (data && data->next)
	// 	process_pipe(data);
	if(data && (data->redir_in || data->redir_out || data->append || data->heredoc))
		{	
			if(data->redir_in)
				if (ft_input(data->redir_in))
					return ;
			if(data->redir_out)
			{
				if (ft_output(data->redir_out))
					return ;
			}
		}
	
	// if(data && !data->cmd)
	// 	return;
	
	if(data->cmd)
	{	if(data && !ft_strcmp(data->args[0],"./minishell"))
			inc_shell();
		else if(data && !ft_strcmp(data->args[0],"exit"))
			dec_shell();}
	
	// if (data && !data->cmd)
	// 	return ;
	
	if(check_builts(data))
		handle_builts(data);
	else
	{
		pid = fork();
		if(!pid)
		{
				execute(data);
		}
		while (waitpid(pid, &status, 0) != -1)
		{
			if (WIFEXITED(status))
			{
				status = WEXITSTATUS(status);
				if (status == 127 || status == 1 || status == 0)
					break ;
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
