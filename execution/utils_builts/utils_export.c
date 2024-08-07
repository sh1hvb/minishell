/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 20:12:24 by mchihab           #+#    #+#             */
/*   Updated: 2024/08/01 18:51:37 by mchihab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

t_envp	*sort_list(t_envp *lst, int (*cmp)(int, int))
{
	int		swapped;
	t_envp	*ptr1;
	t_envp	*lptr;

	lptr = NULL;
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
	}
	set_previous_pointers(lst);
	return (lst);
}

t_envp	*my_append_env(t_envp *env_list, const char *key, char *value, int flag)
{
	t_envp	*tmp;

	(void)flag;
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

void	ft_append(t_data *data, t_envp *env, int i)
{
	char	*append;
	char	*join;
	int		flag;
	char	**temp_splited;
	char	*sp;

	flag = 0;
	append = my_get_env(env, lexer_split(data->args[i], "+=")[0]);
	if (!append)
	{
		flag = if_flag(data->args[i]);
		ft_lstadd_back_env(&env, ft_lstnew_env(data->args[i], env, flag));
	}
	else
	{
		temp_splited = split_with_first_delimiter(data->args[i], "=");
		join = ft_strjoin(append, temp_splited[1]);
		if (clean_plus_from_key(temp_splited[0]))
			sp = lexer_split(temp_splited[0], "+")[0];
		else
			sp = temp_splited[0];
		env = my_append_env(env, sp, join, 0);
		ft_freed(temp_splited);
	}
	free(append);
}
