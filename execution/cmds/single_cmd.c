#include "../../minishell.h"



void execute_single_cmd(t_data *data)
{
    if (data && check_heredoc(data))
        handle_heredoc(data);
    handle_redirections(data);
    if (data->cmd)
    {
        if (data && !ft_strcmp(data->args[0], "./minishell"))
            inc_shell();
    }
    if (check_builts(data))
        handle_builts(data);
    else
        handle_child_process(data);
    cleanup_redirections(data);
}

void handle_heredoc(t_data *data)
    heredoc(data);

void handle_redirections(t_data *data)
{
    int index;

    if (data && (data->redir_in || data->redir_out || data->append || data->heredoc))
    {
        if (data->append && ft_append_file(data->append))
            return;
        if (data->redir_in && ft_input(data->redir_in))
            return;
        if (data->redir_out && ft_output(data->redir_out))
            return;

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
}

void handle_child_process(t_data *data)
{
    int pid, status;

    pid = fork();
    if (!pid)
    {
        if (!data->cmd)
            exit(0);
        execute(data);
    }

    while (waitpid(pid, &status, 0) != -1)
    {
        if (WIFEXITED(status))
        {
            status = WEXITSTATUS(status);
            env->exit_status = status;
            if (status == 127 || status == 126 || status == 1 || status == 0)
                break;
        }
        else if (WIFSIGNALED(status))
        {
            env->exit_status = WTERMSIG(status) + 128;
            break;
        }
    }
}

void cleanup_redirections(t_data *data)
{
    if (ft_lstlast_file(data->redir_in) && ft_lstlast_file(data->redir_in)->index)
        close(ft_lstlast_file(data->redir_in)->index);
    if (ft_lstlast_file(data->redir_out) && ft_lstlast_file(data->redir_out)->index)
        close(ft_lstlast_file(data->redir_out)->index);
    if (ft_lstlast_file(data->heredoc) && ft_lstlast_file(data->heredoc)->index)
        close(ft_lstlast_file(data->heredoc)->index);
}