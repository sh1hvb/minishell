#include "../../minishell.h"


void execute(t_data *data)
{
    char *path;
    char **envp;

    check_command_validity(data);

    path = get_execution_path(data);
    envp = list_to_pointer();

    check_path_validity(path, data);

    handle_redirections(data);

    if ((data && !data->cmd) || !data->cmd[0])
        exit(127);

    execute_command(path, data, envp);
}

void check_command_validity(t_data *data)
{
    if (data && data->cmd)
    {
        if (!ft_strcmp("minishell", data->args[0]))
        {
            ft_putstr_fd(data->cmd, 2);
            ft_putendl_fd(": command not found", 2);
            exit(127);
        }
    }
}

char *get_execution_path(t_data *data)
{
    return get_path(data->cmd);
}

void check_path_validity(char *path, t_data *data)
{
    if (path)
    {
        if (data->cmd[0] == '/' && access(path, X_OK) != 0)
        {
            ft_putstr_fd("minishell: ", 2);
            ft_putstr_fd(data->cmd, 2);
            ft_putstr_fd(": No such file or directory\n", 2);
            exit(127);
        }

        int fd = open(path, __O_DIRECTORY);
        if (fd != -1)
        {
            free(path);
            ft_freed(envp);
            ft_putstr_fd("minishell: ", 2);
            ft_putstr_fd(data->cmd, 2);

            if (data->cmd[0] == '/' || data->cmd[ft_strlen(data->cmd) - 1] == '/' || (data->cmd[0] == '.' && data->cmd[1] == '/'))
            {
                ft_putstr_fd(": Is a directory\n", 2);
                exit(126);
            }
            else
            {
                ft_putstr_fd(": command not found\n", 2);
                exit(127);
            }
        }
    }
}

void handle_redirectionss(t_data *data)
{
    int index;

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

void execute_commands(char *path, t_data *data, char **envp)
{
    if (execve(path, data->args, envp) == -1 || access(path, X_OK & F_OK) != 0)
    {
        ft_putstr_fd(data->cmd, 2);
        if (access(path, X_OK & F_OK) != 0 && (data->cmd[0] == '/' || data->cmd[ft_strlen(data->cmd) - 1] == '/' || (data->cmd[0] == '.' && data->cmd[1] == '/')))
            ft_putstr_fd(": No such file or directory\n", 2);
        else
            ft_putendl_fd(": command not found", 2);
        exit(127);
    }
}