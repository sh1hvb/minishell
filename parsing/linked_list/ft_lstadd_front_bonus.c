/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:42:16 by smarsi            #+#    #+#             */
/*   Updated: 2024/05/22 11:03:57 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_data **lst, t_data *new)
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
