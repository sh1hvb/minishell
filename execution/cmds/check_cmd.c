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
	int flag ;
	flag = 0;
	if (data && !data->next && check_builts(data))
	{
		execute_single_cmd(data);
		dup2(199, 0);
		dup2(200, 1);
		flag = 1;
	}
	else if (data && check_heredoc_two(data))
	{
		heredoc_mult(data);
	}
	if (data && data->cmd && data->cmd[0] && !flag)
	{
		process_pipe(data);
		dup2(199, 0);
		dup2(200, 1);
		while (waitpid(-1, &status, 0) != -1);
	}
	else if(data && data->cmd && data->cmd[0] == '\0')
	{
		ft_putendl_fd("command '' not found",2);
	}

}