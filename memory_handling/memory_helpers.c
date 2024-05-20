/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:21:24 by smarsi            #+#    #+#             */
/*   Updated: 2024/05/20 14:34:57 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	free_lstsize(t_leaks *lst)
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

t_leaks	*free_lstlast(t_leaks *lst)
{
	int	last;

	last = free_lstsize(lst);
	while (last-- > 1)
		lst = lst->next;
	return (lst);
}
