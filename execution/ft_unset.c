/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 20:20:32 by mchihab           #+#    #+#             */
/*   Updated: 2024/08/02 20:20:39 by mchihab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*free_env(t_envp *g_env)
{
	free(g_env->key);
	g_env->key = NULL;
	free(g_env->value);
	g_env->value = NULL;
	free(g_env);
	g_env = NULL;
	return (g_env);
}
void		ft_unset(char **args)
{
	t_envp	*save;
	t_envp	*prev;
	int		i;

	i = 1;
	save = g_env;
	while (args[i++] && !(prev = NULL))
	{
		g_env = save;
		while (g_env)
		{
			if (!ft_strcmp(g_env->key, args[i - 1]))
			{
				if (prev)
					prev->next = g_env->next;
				else
					save = g_env->next;
				free_env(g_env);
				break ;
			}
			prev = g_env;
			g_env = g_env->next;
		}
	}
	g_env = save;
	// return (!(g_env = save));
}
// void	condition(t_envp *head)
// {
// 	if (!head->prev)
// 	{
// 		g_env = head->next;
// 		if (g_env)
// 			g_env->prev = NULL;
// 	}
// 	else
// 	{
// 		head->prev->next = head->next;
// 		if (head->next)
// 			head->next->prev = head->prev;
// 	}
// }

// void	remove_node(t_envp *head, t_data *data, int i)
// {
// 	t_envp	*tmp;

// 	tmp = NULL;
// 	while (head)
// 	{
// 		if (!ft_strcmp(data->args[i], head->key) && ft_strcmp(data->args[i],
// 				"_"))
// 		{
// 			condition(head);
// 			free(head->key);
// 			free(head->value);
// 			tmp = head;
// 			head = head->next;
// 			free(tmp);
// 			break ;
// 		}
// 		else
// 			head = head->next;
// 	}
// }

// void	ft_unset(t_data *data)
// {
// 	int		i;
// 	t_envp	*head;

// 	i = 1;
// 	while (data->args[i])
// 	{
// 		head = g_env;
// 		remove_node(head, data, i);
// 		i++;
// 	}
// }
