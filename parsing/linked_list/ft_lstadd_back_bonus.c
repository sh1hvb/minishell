/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:05:11 by smarsi            #+#    #+#             */
/*   Updated: 2024/05/22 11:03:54 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_data **lst, t_data *new)
{
	t_data	*head;
	int		i;

	if (!lst)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		head = ft_lstlast(*lst);
		new->prev = head;
		head->next = new;
	}
}
