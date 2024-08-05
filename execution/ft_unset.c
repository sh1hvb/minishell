/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 20:20:32 by mchihab           #+#    #+#             */
/*   Updated: 2024/08/05 11:57:37 by mchihab          ###   ########.fr       */
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

void	unset_variable(t_envp **save, char *arg)
{
	t_envp	*prev;

	g_env = *save;
	prev = NULL;
	while (g_env)
	{
		if (!ft_strcmp(g_env->key, arg) && ft_strcmp(g_env->key, "_"))
		{
			if (prev)
				prev->next = g_env->next;
			else
				*save = g_env->next;
			free_env(g_env);
			return ;
		}
		prev = g_env;
		g_env = g_env->next;
	}
}

void	ft_unset(char **args)
{
	t_envp	*save;
	int		i;

	save = g_env;
	i = 1;
	while (args[i])
	{
		unset_variable(&save, args[i]);
		i++;
	}
	g_env = save;
}
