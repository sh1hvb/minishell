/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 17:03:52 by smarsi            #+#    #+#             */
/*   Updated: 2024/05/22 11:10:02 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_data *lst)
{
	if (lst)
	{
		free(lst->cmd);
		lst->cmd = NULL;
		free(lst);
		lst = NULL;
	}
}
