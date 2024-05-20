/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 06:28:24 by smarsi            #+#    #+#             */
/*   Updated: 2024/05/16 07:11:30 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_cmds(char *prompt, t_data **data, int *index)
{
	int	i;

	i = *index;
	if (prompt[i] && in_delimiters(prompt[i], " \t\n\v\v\f\r"))
	{
		printf("%c", prompt[i]);
		i++;
	}
	while (prompt[i] && !in_delimiters(prompt[i], " \t\n\v\v\f\r"))
	{
		printf("%c", prompt[i]);
		i++;
	}
	*index = i;
}

void	get_quotes(char *prompt, t_data **data, int *index)
{
	char	c;
	int		i;

	i = *index;
	c = prompt[i];
	printf("%c", c);
	i++;
	while (prompt[i] && c != prompt[i])
	{
		printf("%c", prompt[i]);
		i++;
	}
	if (c == prompt[i])
		printf("%c", prompt[i++]);
	printf("\n");
	*index = i;
}
