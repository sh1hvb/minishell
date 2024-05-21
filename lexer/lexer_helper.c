/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 06:14:57 by smarsi            #+#    #+#             */
/*   Updated: 2024/05/20 10:27:46 by smarsi           ###   ########.fr       */
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

void	get_cmds(char *prompt, t_data **data, int *index)
{
	int	i;

	(void) data;
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

	(void) data;
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