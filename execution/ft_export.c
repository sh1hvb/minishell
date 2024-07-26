/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 20:19:08 by mchihab           #+#    #+#             */
/*   Updated: 2024/07/26 20:20:00 by mchihab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(void)
{
	print_env_list("en");
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

void	handle_flag_set(t_data *data, t_envp *env, int i, char **arr)
{
	int		flag;
	char	*tmp;

	tmp = NULL;
	flag = if_flag(data->args[i]);
	if (check_string(data->args[i]) == 2)
		ft_append(data, env, i);
	else if (check_string(data->args[i]) == 1)
	{
		tmp = my_get_env(env, arr[0]);
		if (tmp)
		{
			if (arr[1])
				my_append_env(env, arr[0], ft_strdup(arr[1]));
			else if (check_equal(data->args[i]))
				my_append_env(env, arr[0], ft_strdup(""));
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
	}
	arr = builtins_split(data->args[i], "+=");
	if (handle_no_first_element(arr))
		return ;
	if ((!ft_isdigit(data->args[i][0])) && check_string(data->args[i]))
		handle_flag_set(data, env, i, arr);
	else
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(data->args[1], 2);
		ft_putendl_fd("': not a valid identifier", 2);
		env->exit_status = 1;
	}
	ft_freed(arr);
}

void	ft_export(t_data *data, t_envp *env)
{
	int	i;

	i = 1;
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
