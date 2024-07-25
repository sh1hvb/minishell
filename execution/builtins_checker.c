#include "../minishell.h"

int	check_builts(t_data *data)
{
	if (!data->cmd || !data->args)
		return (0);
	if (!ft_strcmp(data->cmd, "echo"))
		return (1);
	else if (!ft_strcmp(data->cmd, "cd"))
		return (2);
	else if (!ft_strcmp(data->cmd, "pwd"))
		return (3);
	else if (!ft_strcmp(data->cmd, "export"))
		return (4);
	else if (!ft_strcmp(data->cmd, "unset"))
		return (5);
	else if (!ft_strcmp(data->cmd, "env"))
		return (6);
	else if (!ft_strcmp(data->cmd, "exit"))
		return (7);
	return (0);
}
void	handle_builts(t_data *data)
{
	t_envp *envtmp;
	envtmp = env;
	if (!check_builts(data))
		ft_error(" command not found", 127);
	if (check_builts(data) == 1)
		ft_echo(data);
	if (check_builts(data) == 2)
		ft_cd(data);
	if (check_builts(data) == 3)
		ft_pwd(data);
	if (check_builts(data) == 4)
		ft_export(data, envtmp);
	if (check_builts(data) == 5)
		ft_unset(data);
	if (check_builts(data) == 6)
		ft_env(envtmp);
	if (check_builts(data) == 7)
		ft_exit(data);
}