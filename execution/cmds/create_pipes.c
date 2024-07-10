#include "../../minishell.h"




void setup_pipe(int fds[2])
{
    if (pipe(fds) == -1)
    {
        perror("pipe");
        exit(1);
    }
}

void handle_redirections(t_data *data, int fds[2], int *flag)
{
    t_files *file;
    (void)fds;
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
        *flag = 1;
    }
    if (data && data->append)
    {
        if (ft_append_file(data->append))
            exit(1);
        file = ft_lstlast_file(data->append);
        dup2(file->index, 1);
        close(file->index);
    }
}

void execute_command_in_child(t_data *data, int fds[2], int flag)
{
    if ((data && !data->cmd) || !data->cmd[0])
        exit(127);
    close(fds[0]);
    if (!flag)
        dup2(fds[1], 1);
    else
        close(fds[1]);
    if (!check_builts(data))
        exec(data);
    else
    {
        handle_builts(data);
        exit(0);
    }
}

void handle_parent_process(int fds[2], t_data *data)
{
    if (!check_heredoc_two(data))
    {
        close(fds[1]);
        dup2(fds[0], 0);
        close(fds[0]);
    }
}

void create_pipes(t_data *data)
{
    int pid, fds[2], flag = 0;

    setup_pipe(fds);

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return;
    }
    if (!pid)
    {
        handle_redirections(data, fds, &flag);
        execute_command_in_child(data, fds, flag);
    }

    handle_parent_process(fds, data);
}