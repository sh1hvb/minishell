#include "../../minishell.h"


void ft_execute_multiple(t_data *data)
{
    int pid, status;

    create_pipes_for_all(data);

    pid = fork();
    if (!pid)
    {
        handle_redirectionss(data);

        if ((data && !data->cmd) || !data->cmd[0])
            exit(127);
        else if (!check_builts(data))
        {
            exec(data);
            while (waitpid(pid, &status, 0) != -1);
            if (WIFEXITED(status))
                env->exit_status = WIFEXITED(status);
            else if (WIFSIGNALED(status))
                env->exit_status = WTERMSIG(status) + 128;
        }
        else if (check_builts(data))
        {
            handle_builts(data);
            exit(0);
        }
    }
}

void create_pipes_for_all(t_data *data)
{
    while (data && data->next)
    {
        create_pipes(data);
        data = data->next;
    }
}

void handle_redirectionss(t_data *data)
{
    t_files *file;

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

void execute_commands(t_data *data)
{
    if (!check_builts(data))
    {
        exec(data);
        int status;
        while (waitpid(-1, &status, 0) != -1)
        {
            if (WIFEXITED(status))
                env->exit_status = WEXITSTATUS(status);
            else if (WIFSIGNALED(status))
                env->exit_status = WTERMSIG(status) + 128;
        }
    }
    else
    {
        handle_builts(data);
        exit(0);
    }
}