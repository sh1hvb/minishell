/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_strchr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 06:00:12 by smarsi            #+#    #+#             */
/*   Updated: 2024/05/19 19:03:13 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	lexer_strchr(char *str, char *dlmtrs, int *ind, int f)
{
	int	i;

	i = *ind;
	while (str[i] && in_delimiters(str[i], dlmtrs) == f)
		i++;
	*ind = i;
}