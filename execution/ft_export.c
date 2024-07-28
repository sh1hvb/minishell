/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 20:19:08 by mchihab           #+#    #+#             */
/*   Updated: 2024/07/28 20:49:18 by mchihab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(void)
{
	move_key_to_end("_");
	print_env_list(g_env, "en");
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

void	handle_flag_set(t_data *data, t_envp *g_env, int i, char **arr)
{
	int		flag;
	char	*tmp;

	tmp = NULL;
	flag = if_flag(data->args[i]);
	if (check_string(data->args[i]) == 2)
		ft_append(data, g_env, i);
	else if (check_string(data->args[i]) == 1)
	{
		tmp = my_get_env(g_env, arr[0]);
		if (tmp)
		{
			if (arr[1])
				my_append_env(g_env, arr[0], ft_strdup(arr[1]));
			else if (check_equal(data->args[i]))
				my_append_env(g_env, arr[0], ft_strdup(""));
			free(tmp);
		}
		else if (!tmp || check_equal(data->args[i]))
			(ft_lstadd_back_env(&g_env, ft_lstnew_env(data->args[i], g_env,
						flag)), free(tmp));
	}
	g_env->exit_status = 0;
}

void	process_arguments(t_data *data, t_envp *g_env, int i)
{
	char	**arr;

	if (!ft_strcmp(data->args[1], "=") || !ft_strcmp(data->args[1], "+="))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(data->args[i], 2);
		ft_putendl_fd("': not a valid identifier", 2);
		g_env->exit_status = 1;
	}
	arr = builtins_split(data->args[i], "+=");
	if (handle_no_first_element(arr))
		return ;
	if ((!ft_isdigit(data->args[i][0])) && check_string(data->args[i]))
		handle_flag_set(data, g_env, i, arr);
	else
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(data->args[i], 2);
		ft_putendl_fd("': not a valid identifier", 2);
		g_env->exit_status = 1;
	}
	ft_freed(arr);
}

void	ft_export(t_data *data, t_envp *g_env)
{
	int	i;

	i = 1;
	if (!ft_strcmp(data->args[0], "export") && (!data->args[1]))
	{
		handle_no_arguments(g_env);
		return ;
	}
	while (data->args[i])
	{
		if (!ft_strcmp(data->args[i], "export"))
			i++;
		process_arguments(data, g_env, i);
		i++;
	}
}
