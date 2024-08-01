/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 20:40:19 by mchihab           #+#    #+#             */
/*   Updated: 2024/08/01 19:00:10 by mchihab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstadd_back_env(t_envp **lst, t_envp *new)
{
	t_envp	*head;

	if (!lst)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		head = ft_lstlast_env(*lst);
		head->next = new;
	}
}

char	**list_to_pointer(void)
{
	int		i;
	char	**arr;
	char	*tmp;
	t_envp	*lst;

	lst = g_env;
	i = 0;
	tmp = NULL;
	arr = ft_calloc((ft_lstsize_env(lst) + 1), sizeof(char *));
	if (!arr)
		return (NULL);
	while (lst)
	{
		if (!lst->value)
			arr[i] = ft_strjoin(lst->key, NULL);
		else
		{
			tmp = ft_strjoin(lst->key, "=");
			arr[i] = ft_strjoin(tmp, lst->value);
			free(tmp);
		}
		i++;
		lst = lst->next;
	}
	return (arr);
}

void	inc_shell(void)
{
	int		tmp;
	t_envp	*tmpenv;

	tmpenv = g_env;
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

int	check_string(char *s)
{
	int	i;

	i = 0;
	if (s[0] == '=')
		return (0);
	while (s[i])
	{
		if (s[i] == '=')
			return (1);
		if (!ft_isalnum(s[i]))
		{
			if (s[i] == '+' && s[i + 1] == '=')
				return (2);
			return (0);
		}
		i++;
	}
	return (1);
}

void	move_key_to_end(char *key)
{
	t_envp	*current;
	t_envp	*previous;
	t_envp	*target;
	t_envp	*target_prev;

	current = g_env;
	while (current)
	{
		if (strcmp(current->key, key) == 0)
		{
			target = current;
			target_prev = previous;
		}
		previous = current;
		current = current->next;
	}
	if (target && target->next)
	{
		if (target == g_env)
			g_env = target->next;
		else
			target_prev->next = target->next;
		previous->next = target;
		target->next = NULL;
	}
}
