/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_strchr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 12:21:02 by smarsi            #+#    #+#             */
/*   Updated: 2024/07/27 12:21:04 by smarsi           ###   ########.fr       */
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

void	lexer_strchr_d(char *str, char *dlmtrs, int *ind, int f)
{
	int	i;

	(void)dlmtrs;
	(void)f;
	i = *ind;
	if (str[i] == '?')
		i++;
	else
	{
		while (str[i] && (ft_isalpha(str[i]) || ft_isdigit(str[i]) \
		|| str[i] == '_'))
			i++;
	}
	*ind = i;
}
