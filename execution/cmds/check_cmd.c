#include "../../minishell.h"

char	**list_to_pointer(void)
{
	int		i;
	char	**arr;
	char	*tmp;
	int		size;
	t_envp	*lst;

	lst = env;
	i = 0;
	arr = NULL;
	tmp = NULL;
	size = ft_lstsize_env(ls);
	arr = malloc((size + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	while (ls)
	{
		tmp = ft_strjoin(ls->key, "=");
		arr[i] = ft_strjoin(tmp, ls->value);
		free(tmp);
		i++;
		ls = ls->next;
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
			if (tmp > 1000)
			{
				tmpenv->value = (ft_itoa(1));
				ft_putendl_fd("bash: warning: shell level (1001) too high,\
						resetting to 1", 2);
			}
			else
				tmpenv->value = (ft_itoa(tmp));
			break ;
		}
		tmpenv = tmpenv->next;
	}
}

void	check_redir(t_data *data, t_files *file)
{
	if (data && data->redir_in)
	{
		if (ft_input(data->redir_in))
			return ;
		file = ft_lstlast_file(data->redir_in);
		dup2(file->index, 0);
		close(file->index);
	}
	if (data && data->redir_out)
	{
		if (ft_output(data->redir_out))
			return ;
		file = ft_lstlast_file(data->redir_out);
		dup2(file->index, 1);
		close(file->index);
	}
	if (data && data->append)
	{
		if (ft_append_file(data->append))
			return ;
		file = ft_lstlast_file(data->append);
		dup2(file->index, 1);
		close(file->index);
	}
}

void	hide_inout(int a)
{
	if (!a)
	{
		dup2(0, 199);
		dup2(1, 200);
	}
	else
	{
		dup2(199, 0);
		dup2(200, 1);
	}
}

void	check_empty_cmd(t_data *data)
{
	if (data && data->cmd && data->cmd[0] == '\0')
	{
		ft_putendl_fd("command '' not found", 2);
		return ;
	}
}

void	process_cmd(t_data *data)
{
	t_files	*file;

	int (status), (flag);
	file = NULL;
	flag = 0;
	env->signal_heredoc = 0;
	hide_inout(0);
	if (data && check_heredoc_two(data))
		heredoc_mult(data);
	if (data && !data->next && check_builts(data) && !env->signal_heredoc)
	{
		execute_single_cmd(data);
		hide_inout(1);
		flag = 1;
	}
	else if (data && !flag && !env->signal_heredoc)
	{
		process_pipe(data);
		hide_inout(1);
		while (waitpid(-1, &status, 0) != -1)
			;
	}
	else if (data)
		check_redir(data, file);
}
