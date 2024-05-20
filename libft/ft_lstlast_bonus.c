/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:53:26 by smarsi            #+#    #+#             */
/*   Updated: 2024/05/19 18:36:47 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lexer	*ft_lstlast(t_lexer *lst)
{
	int	last;

	last = ft_lstsize(lst);
	while (last-- > 1)
		lst = lst->next;
	return (lst);
}
