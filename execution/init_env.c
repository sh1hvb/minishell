/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 20:32:45 by mchihab           #+#    #+#             */
/*   Updated: 2024/07/26 20:39:48 by mchihab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_envp	*init_env_node(void)
{
	t_envp	*new_node;

	new_node = malloc(sizeof(t_envp));
	if (!new_node)
		return (NULL);
	new_node->key = NULL;
	new_node->value = NULL;
	new_node->flag = 0;
	new_node->signal_heredoc = 0;
	new_node->exit_status = 0;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

static void	fill_env_node(t_envp *node, char **splited, int c)
{
	node->key = ft_strdup(splited[0]);
	if (c)
		node->value = ft_strdup(splited[1]);
	else
		node->value = ft_strdup(getenv(splited[0]));
}

t_envp	*build_env_list(char **env, int c)
{
	t_envp	*env_list;
	t_envp	*current;
	t_envp	*new_node;
	char	**splited;
	int		i;

	env_list = NULL;
	current = NULL;
	i = 0;
	while (env[i])
	{
		splited = builtins_split(env[i], "+=");
		new_node = init_env_node();
		if (!new_node)
			return (NULL);
		fill_env_node(new_node, splited, c);
		new_node->prev = current;
		if (current)
			current->next = new_node;
		else
			env_list = new_node;
		current = new_node;
		(ft_freed(splited), i++);
	}
	return (env_list);
}
