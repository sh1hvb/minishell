/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:04:47 by smarsi            #+#    #+#             */
/*   Updated: 2024/05/31 15:05:24 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lexer	*ft_lstnew(char *value, int type, int quotes)
{
	t_lexer	*head;

	head = ft_malloc(sizeof(t_lexer), 0);
	if (!head)
		return (NULL);
	head->value = value;
	head->type = type;
	head->in_quotes = quotes;
	head->next = NULL;
	head->prev = NULL;
	return (head);
}
