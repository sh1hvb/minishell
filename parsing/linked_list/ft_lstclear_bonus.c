/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 11:17:32 by smarsi            #+#    #+#             */
/*   Updated: 2024/05/22 11:03:59 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_data **lst)
{
	t_data	*next;

	if (!lst)
		return ;
	while (*lst)
	{
		next = (*lst)->next;
		ft_lstdelone(*lst);
		*lst = next;
	}
}
