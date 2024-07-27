/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 20:20:49 by mchihab           #+#    #+#             */
/*   Updated: 2024/07/26 20:21:21 by mchihab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_lstsize_env(t_envp *lst)
{
	int	count;

	if (!lst)
		return (0);
	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

void	ft_lstadd_front_env(t_envp **lst, t_envp *new)
{
	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		new->next = NULL;
	}
	else
	{
		new->next = *lst;
		*lst = new;
	}
}

t_envp	*ft_lstlast_env(t_envp *lst)
{
	int	last;

	last = ft_lstsize_env(lst);
	while (last-- > 1)
		lst = lst->next;
	return (lst);
}

void	ft_lstdelone_env(t_envp *lst)
{
	if (lst)
	{
		free(lst->value);
		lst->value = NULL;
		free(lst->key);
		lst->key = NULL;
		free(lst);
		lst = NULL;
	}
}

t_envp	*ft_lstnew_env(char *value, t_envp *env, int flag)
{
	t_envp	*head;
	char	**splited;
	t_envp	*last;

	splited = NULL;
	last = ft_lstlast_env(env);
	splited = builtins_split(value, "+=");
	head = malloc(sizeof(t_envp));
	if (!head)
		return (NULL);
	head->key = splited[0];
	head->value = splited[1];
	head->flag = flag;
	head->next = NULL;
	head->prev = last;
	free(splited);
	return (head);
}
