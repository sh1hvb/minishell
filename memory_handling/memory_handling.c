/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 18:23:38 by mchihab           #+#    #+#             */
/*   Updated: 2024/07/28 18:23:39 by mchihab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_lstadd_back(t_leaks **lst, t_leaks *new)
{
	static t_leaks	*head;

	if (!lst)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		head = free_lstlast(*lst);
		head->next = new;
	}
}

t_leaks	*free_lstnew(char *value)
{
	t_leaks	*head;

	head = malloc(sizeof(t_leaks));
	if (!head)
		return (NULL);
	head->add = value;
	head->next = NULL;
	return (head);
}

void	free_lstclear(t_leaks **lst)
{
	t_leaks	*next;

	if (!lst)
		return ;
	while (*lst)
	{
		next = (*lst)->next;
		if (*lst)
		{
			if ((*lst)->add)
				free((*lst)->add);
			free(*lst);
		}
		*lst = next;
	}
	*lst = NULL;
}

void	*ft_malloc(int size, int flag)
{
	static t_leaks	*address;
	void			*p;
	t_leaks			*new_node;

	p = NULL;
	if (flag)
		free_lstclear(&address);
	else
	{
		p = malloc(size);
		if (!p)
		{
			ft_malloc(0, 1);
			return (NULL);
		}
		new_node = free_lstnew(p);
		if (!new_node)
		{
			free(p);
			ft_malloc(0, 1);
			return (NULL);
		}
		free_lstadd_back(&address, new_node);
	}
	return (p);
}
