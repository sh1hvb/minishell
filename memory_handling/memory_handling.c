/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:14:13 by smarsi            #+#    #+#             */
/*   Updated: 2024/05/20 16:08:21 by mchihab          ###   ########.fr       */
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
            free((*lst)->add);
            free(*lst);
	    }
		*lst = next;
	}
}

void *ft_malloc(int size, int flag)
{
   	static t_leaks *address;
    void *p;

	p = NULL;
    if (flag)
        free_lstclear(&address);
    else
    {
        p = (void *)malloc(size);
        free_lstadd_back(&address, free_lstnew(p));
    }
    return (p);
}
