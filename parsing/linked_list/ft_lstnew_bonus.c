/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:04:47 by smarsi            #+#    #+#             */
/*   Updated: 2024/05/22 11:09:26 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_data	*ft_lstnew(char *value, int type, int quotes, char *in, char *out)
{
	t_data	*head;

	head = ft_malloc(sizeof(t_data), 0);
	if (!head)
		return (NULL);
	head->cmd = value;
	head->args = NULL;
	head->in_quotes = quotes;
	head->redir_in = in;
	head->redir_out = out;
	head->next = NULL;
	head->prev = NULL;
	return (head);
}

