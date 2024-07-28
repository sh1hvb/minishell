/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 20:20:32 by mchihab           #+#    #+#             */
/*   Updated: 2024/07/28 18:06:19 by mchihab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	condition(t_envp *head)
{
	if (!head->prev)
	{
		g_env = head->next;
		if (g_env)
			g_env->prev = NULL;
	}
	else
	{
		head->prev->next = head->next;
		if (head->next)
			head->next->prev = head->prev;
	}
}

void	remove_node(t_envp *head, t_data *data, int i)
{
	t_envp	*tmp;

	tmp = NULL;
	while (head)
	{
		if (!ft_strcmp(data->args[i], head->key) && ft_strcmp(data->args[i],
				"_"))
		{
			condition(head);
			free(head->key);
			free(head->value);
			tmp = head;
			head = head->next;
			free(tmp);
			break ;
		}
		else
			head = head->next;
	}
}

void	ft_unset(t_data *data)
{
	int		i;
	t_envp	*head;

	i = 1;
	while (data->args[i])
	{
		head = g_env;
		remove_node(head, data, i);
		i++;
	}
}
