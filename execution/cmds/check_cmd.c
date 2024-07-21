#include "../../minishell.h"

char	**list_to_pointer(void)
{
	int		i;
	char	**arr;
	char	*tmp;
	int		size;

	i = 0;
	arr = NULL;
	tmp = NULL;
	size = ft_lstsize_env(env);
	arr = malloc((size + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	while (env)
	{
		tmp = ft_strjoin(env->key, "=");
		arr[i] = ft_strjoin(tmp, env->value);
		free(tmp);
		i++;
		env = env->next;
	}
	arr[i] = NULL;
	return (arr);
}
void	inc_shell(void)
{
	int		tmp;
	t_envp	*tmpenv;

	tmpenv = env;
	while (tmpenv)
	{
		if (!ft_strcmp(tmpenv->key, "SHLVL"))
		{
			tmp = ft_atoi(tmpenv->value) + 1;
			free(tmpenv->value);
			tmpenv->value = (ft_itoa(tmp));
			break ;
		}
		tmpenv = tmpenv->next;
	}
}

void	process_cmd(t_data *data)
{
	dup2(0, 199);
	dup2(1, 200);
	int(status);
	if (data && !data->next && check_builts(data))
	{
		execute_single_cmd(data);
		dup2(199, 0);
		dup2(200, 1);
	}
	else if (data && check_heredoc_two(data))
	{
		heredoc_mult(data);
		while (waitpid(-1, &status, 0) != -1);
	}
	else if (data && data->cmd && data->cmd[0])
	{
		process_pipe(data);
		dup2(199, 0);
		dup2(200, 1);
		while (waitpid(-1, &status, 0) != -1)
		{
			if (WIFEXITED(status))
			{
				status = WEXITSTATUS(status);
				env->exit_status = status;
				if (status == 127 || status == 126 || status == 1
					|| status == 0)
				{
					break ;
				}
			}
			else if (WIFSIGNALED(status))
			{
				env->exit_status = WTERMSIG(status) + 128;
				break ;
			}
		}
	}
	else if(data->cmd[0] == '\0' && data->args[0][0]!='$')
	{
		ft_putendl_fd("command '' not found",2);
	}

}