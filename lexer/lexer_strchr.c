/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_strchr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 06:00:12 by smarsi            #+#    #+#             */
/*   Updated: 2024/05/21 12:25:32 by smarsi           ###   ########.fr       */
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

	i = *ind;
	while (str[i] && ((in_delimiters(str[i], dlmtrs) == f) || ft_isalpha(str[i]) || ft_isdigit(str[i])))
		i++;
	*ind = i;
}