/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 06:14:57 by smarsi            #+#    #+#             */
/*   Updated: 2024/05/21 14:39:13 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	in_delimiters(char target, char *delimiters)
{
	int	i;

	i = 0;
	while (delimiters[i])
	{
		if (target == delimiters[i])
			return (1);
		i++;
	}
	return (0);
}

void	skip_quotes(char *target, char delimiter, int *index)
{
	int	i;

	i = *index;
	i++;
	while (target[i] && target[i] != delimiter)
		i++;
	if (target[i] == delimiter)
		i++;
	*index = i;
}
