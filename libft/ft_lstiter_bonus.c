/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 11:46:25 by smarsi            #+#    #+#             */
/*   Updated: 2024/05/19 18:41:14 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_lexer **lst)
{
	t_lexer	*tmp;
	char	*i;

	if (!lst)
		return ;
	tmp = *lst;
	i = "test";
	while (tmp)
	{
		tmp->value = i;
		tmp = tmp->next;
		i++;
	}
}
