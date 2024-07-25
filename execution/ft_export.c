#include "../minishell.h"

int	if_flag(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			return (1);
		i++;
	}
	return (0);
}
int	ascending(int a, int b)
{
	return (a <= b);
}
static void	swap_nodes(t_envp *a, t_envp *b)
{
	char	*temp_key;
	char	*temp_value;
	int		tmp_flag;

	tmp_flag = a->flag;
	a->flag = b->flag;
	b->flag = tmp_flag;
	temp_key = a->key;
	temp_value = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = temp_key;
	b->value = temp_value;
}
static void	set_previous_pointers(t_envp *lst)
{
	t_envp	*tmp;
	t_envp	*prev;

	tmp = lst;
	prev = NULL;
	while (tmp)
	{
		tmp->prev = prev;
		prev = tmp;
		tmp = tmp->next;
	}
}

char	*my_get_env(t_envp *env_list, const char *key)
{
	t_envp	*current;

	current = env_list;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (!current->value)
				current->value = ft_strdup("");
			return (ft_strdup(current->value));
		}
		current = current->next;
	}
	return (NULL);
}

t_envp	*my_append_env(t_envp *env_list, const char *key, char *value)
{
	t_envp	*tmp;

	tmp = env_list;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			if (tmp->value)
				free(tmp->value);
			tmp->value = ft_strdup(value);
		}
		tmp = tmp->next;
	}
	env_list = tmp;
	free(value);
	return (env_list);
}

t_envp	*sort_list(t_envp *lst, int (*cmp)(int, int))
{
	int		swapped;
	t_envp	*ptr1;
	t_envp	*lptr;

	lptr = NULL;
	if (lst == NULL)
		return (NULL);
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		ptr1 = lst;
		while (ptr1->next != lptr)
		{
			if (!cmp(ptr1->key[0], ptr1->next->key[0]))
			{
				swap_nodes(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	};
	set_previous_pointers(lst);
	return (lst);
}

void	ft_append(t_data *data, t_envp *env, int i)
{
	char	*append;
	char	**splited;
	char	*join;
	int		flag;
	char	**temp_splited;

	flag = 0;
	splited = builtins_split(data->args[i], "+=");
	append = my_get_env(env, splited[0]);
	if (!append)
	{
		flag = if_flag(data->args[i]);
		ft_lstadd_back_env(&env, ft_lstnew_env(data->args[i], env, flag));
	}
	else
	{
		temp_splited = builtins_split(data->args[i], "+=");
		join = ft_strjoin(append, temp_splited[1]);
		env = my_append_env(env, temp_splited[0], join);
		ft_freed(temp_splited);
	}
	free(append);
	ft_freed(splited);
}

int	check_equal(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
		{
			return (1);
		}
		i++;
	}
	return (0);
}

void	handle_no_arguments(t_envp *env)
{
	env = sort_list(env, ascending);
	print_env_list("ex");
}
int	handle_no_first_element(char **arr)
{
	if (!arr[0])
	{
		ft_freed(arr);
		return (1);
	}
	return (0);
}

void	handle_flag_set(t_data *data, t_envp *env, int i, char **arr)
{
	int		flag;
	char	*tmp;

	tmp = NULL;
	flag = if_flag(data->args[i]);
	if (check_string(data->args[i]) == 2)
	{
		ft_append(data, env, i);
	}
	else if (check_string(data->args[i]) == 1)
	{
		tmp = my_get_env(env, arr[0]);
		if (tmp)
		{
			if (arr[1])
			{
				my_append_env(env, arr[0], ft_strdup(arr[1]));
			}
			else if (check_equal(data->args[i]))
			{
				my_append_env(env, arr[0], ft_strdup(""));
			}
			free(tmp);
		}
		else if (!tmp || check_equal(data->args[i]))
		{
			ft_lstadd_back_env(&env, ft_lstnew_env(data->args[i], env, flag));
			free(tmp);
		}
	}
	env->exit_status = 0;
}

void	process_arguments(t_data *data, t_envp *env, int i)
{
	char	**arr;

	if (!ft_strcmp(data->args[1], "=") || !ft_strcmp(data->args[1], "+="))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(data->args[1], 2);
		ft_putendl_fd("': not a valid identifier", 2);
		env->exit_status = 1;
		// return ;
	}
	arr = builtins_split(data->args[i], "+=");
	if (handle_no_first_element(arr))
		return ;
	if ((!ft_isdigit(data->args[i][0])) && check_string(data->args[i]))
	{
		handle_flag_set(data, env, i, arr);
	}
	// if(check_sp(data->args[i]))
	// {
	//     printf("export: `=': not a valid identifier\n");
	//     env->exit_status = 1;
	//     return ;
	// }
	else
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(data->args[1], 2);
		ft_putendl_fd("': not a valid identifier", 2);
		env->exit_status = 1;
		// return ;
	}
	ft_freed(arr);
}

void	ft_export(t_data *data, t_envp *env)
{
	int i = 1;

	if (!ft_strcmp(data->args[0], "export") && (!data->args[1]))
	{
		handle_no_arguments(env);
		return ;
	}

	while (data->args[i])
	{
		if (!ft_strcmp(data->args[i], "export"))
			i++;
		process_arguments(data, env, i);
		i++;
	}
}