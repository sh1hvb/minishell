/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 20:04:56 by mchihab           #+#    #+#             */
/*   Updated: 2024/07/26 20:05:17 by mchihab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_files	*ft_lstlast_file(t_files *lst)
{
	int	last;

	last = ft_lstsize_file(lst);
	while (last-- > 1)
		lst = lst->next;
	return (lst);
}

int	ft_lstsize_file(t_files *lst)
{
	int	count;

	if (!lst)
		return (0);
	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}
