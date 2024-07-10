#include "../../minishell.h"

void handle_child_redirections(t_data *data, int fds[]) {
    t_files *file;
    int flag = 0;
    
    if (data && data->redir_in) {
        if (ft_input(data->redir_in))
            exit(1);
        file = ft_lstlast_file(data->redir_in);
        dup2(file->index, 0);
        close(file->index);
    }
    
    if (data && data->redir_out) {
        if (ft_output(data->redir_out))
            exit(1);
        file = ft_lstlast_file(data->redir_out);
        dup2(file->index, 1);
        close(file->index);
        flag = 1;
    }
    
    if (data && data->append) {
        if (ft_append_file(data->append))
            exit(1);
        file = ft_lstlast_file(data->append);
        dup2(file->index, 1);
        close(file->index);
    }
    
    if (!data->cmd || !data->cmd[0])
        exit(127);
    
    close(fds[0]);
    
    if (!flag)
        dup2(fds[1], 1);
    else
        close(fds[1]);
}
static bool is_directory(char *path)
{
	int fd = open(path, __O_DIRECTORY);
	return (fd != -1);
}

void handle_child_execution(t_data *data) {
    if (!check_builts(data))
        execute(data);
    else {
        handle_builts(data);
        exit(0);
    }
}

void handle_parent_redirections(int fds[]) {
    close(fds[1]);
    dup2(fds[0], 0);
    close(fds[0]);
}

void create_pipes(t_data *data) {
    int fds[2];
    int pid;
    
    if (pipe(fds) == -1) {
        perror("pipe:");
        return;
    }
    
    if ((pid = fork()) == -1) {
        perror("fork");
        return;
    }
    
    if (pid == 0) {
        handle_child_redirections(data, fds);
        handle_child_execution(data);
    } else {
        handle_parent_redirections(fds);
    }
}

	if (!check_heredoc_two(data))
	{
		close(fds[1]);
		dup2(fds[0], 0);
		close(fds[0]);
	}
}
void exec(t_data *data)
{
	char *path;
	char **envp;

	if (!ft_strcmp("minishell", data->args[0]))
	{
		ft_putstr_fd(data->cmd, 2);
		ft_putendl_fd(": command not found", 2);
		return;
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
<<<<<<< HEAD
void ft_execute_multiple(t_data *data)
{
	int pid; //status;
	// t_files *file;

	while (data && data->next)
	{
		create_pipes(data);
		data = data->next;
	}
	pid = fork();
	if (!pid)
		handle_multiple_child(data);
}
=======
void handle_process_redirections(t_data *data) {
    t_files *file;
    
    if (data && data->redir_in) {
        if (ft_input(data->redir_in))
            exit(1);
        file = ft_lstlast_file(data->redir_in);
        dup2(file->index, 0);
        close(file->index);
    }
    if (data && data->redir_out) {
        if (ft_output(data->redir_out))
            exit(1);
        file = ft_lstlast_file(data->redir_out);
        dup2(file->index, 1);
        close(file->index);
    }
    if (data && data->append) {
        if (ft_append_file(data->append))
            exit(1);
        file = ft_lstlast_file(data->append);
        dup2(file->index, 1);
        close(file->index);
    }
    if (!data->cmd || !data->cmd[0])
        exit(127);
}

void handle_process_execution(t_data *data) {
    if (!check_builts(data)) {
        exec(data);
    } else {
        handle_builts(data);
        exit(0);
    }
}

void ft_execute_multiple(t_data *data) {
    // t_data *original_data = data;?
    int pid, status;
    
    while (data && data->next) {
        create_pipes(data);
        data = data->next;
    }
    
    pid = fork();
    if (!pid) {
        handle_process_redirections(data);
        handle_process_execution(data);
    } else {
        waitpid(pid, &status, 0);
        env->exit_status = WEXITSTATUS(status);
        if (WIFSIGNALED(status))
            env->exit_status = WTERMSIG(status) + 128;
    }
}


>>>>>>> main
void process_pipe(t_data *data)
{
	if(data && !ft_strcmp(data->args[0],"./minishell"))
		inc_shell();
	ft_execute_multiple(data);
}

<<<<<<< HEAD
	last = ft_lstsize_file(lst);
	while (last-- > 1)
		lst = lst->next;
	return (lst);
}
void execute(t_data *data)
{
	char *path;
	char **envp;

	if (data && data->cmd)
	{
		if (!ft_strcmp("minishell", data->args[0]))
		{
			ft_putstr_fd(data->cmd, 2);
			ft_putendl_fd(": command not found", 2);
			return;
		}
	}
	path = get_path(data->cmd);
	envp = list_to_pointer();
	if (path)
	{
		if (data->cmd[0] == '/' && access(path, X_OK) != 0)
			handle_no_such_file(data->cmd);
		if (is_directory(path))
		{
			free(path);
			ft_freed(envp);
			handle_directory_error(data->cmd);
		}
	}
	handle_redirection(data);
	if ((data && !data->cmd) || !data->cmd[0])
		exit(127);
	handle_execve(data, path, envp);
}


void execute_single_cmd(t_data *data)
{
	int pid, status;

	if (data && check_heredoc(data))
		heredoc(data);
	handle_redirection_single(data);
	if (data->cmd)
	{
		if (data && !ft_strcmp(data->args[0], "./minishell"))
			inc_shell();
	}
	if (check_builts(data))
		handle_builts(data);
	else
	{
		pid = fork();
		if (!pid)
		{
			if (!data->cmd)
				exit(0);
			execute(data);
		}
		wait_for_child(pid, &status);
	}
	close_redirection_files(data);
}



=======
>>>>>>> main


