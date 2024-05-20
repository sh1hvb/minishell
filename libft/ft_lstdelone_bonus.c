/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 17:03:52 by smarsi            #+#    #+#             */
/*   Updated: 2024/05/20 10:20:26 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_lexer *lst)
{
	if (lst)
	{
		free(lst->value);
		lst->value = NULL;
		free(lst);
		lst = NULL;
	}
}
