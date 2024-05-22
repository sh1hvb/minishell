/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:53:26 by smarsi            #+#    #+#             */
/*   Updated: 2024/05/22 11:04:04 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_data	*ft_lstlast(t_data *lst)
{
	int	last;

	last = ft_lstsize(lst);
	while (last-- > 1)
		lst = lst->next;
	return (lst);
}
