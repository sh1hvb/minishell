#include "../../minishell.h"

void	handle_access_error(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	if (errno == EACCES && (cmd[0] == '/' || cmd[ft_strlen(cmd) - 1] == '/'
			|| (cmd[0] == '.' && cmd[1] == '/')))
	{
		ft_putendl_fd(": Permission denied", 2);
		ft_lstclear_env(env);
		ft_malloc(0, 1);
		exit(126);
	}
	else if (errno == ENOENT && (cmd[0] == '/' || cmd[ft_strlen(cmd) - 1] == '/'
				|| (cmd[0] == '.' && cmd[1] == '/')))
	{
		ft_putendl_fd(": No such file or directory", 2);
		ft_malloc(0, 1);
		ft_lstclear_env(env);
		exit(126);
	}
	else
	{
		ft_lstclear_env(env);
		ft_putendl_fd(": command not found", 2);
		ft_malloc(0, 1);
		exit(127);
	}
}

void	handle_execve_error(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	if (errno == EACCES && (cmd[0] == '/' || cmd[ft_strlen(cmd) - 1] == '/'
			|| (cmd[0] == '.' && cmd[1] == '/')))
	{
		ft_putendl_fd(": Permission denied", 2);
		ft_lstclear_env(env);
		ft_malloc(0, 1);
		exit(126);
	}
	else if (errno == ENOENT && (cmd[0] == '/' || cmd[ft_strlen(cmd) - 1] == '/'
				|| (cmd[0] == '.' && cmd[1] == '/')))
	{
		ft_putendl_fd(": No such file or directory", 2);
		ft_malloc(0, 1);
		ft_lstclear_env(env);
		exit(126);
	}
	else
	{
		ft_putendl_fd(": Command not found", 2);
		ft_lstclear_env(env);
		ft_malloc(0, 1);
		exit(127);
	}
}