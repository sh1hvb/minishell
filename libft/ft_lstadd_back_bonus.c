/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:05:11 by smarsi            #+#    #+#             */
/*   Updated: 2024/05/22 11:15:03 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_lexer **lst, t_lexer *new)
{
	t_lexer	*head;

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
