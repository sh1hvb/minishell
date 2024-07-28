/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_syntax.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 17:58:46 by smarsi            #+#    #+#             */
/*   Updated: 2024/07/28 18:06:19 by mchihab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	pipe_syntax(t_lexer *lex)
{
	t_lexer	*tmp;

	tmp = NULL;
	if (lex)
	{
		tmp = lex;
		tmp = tmp->prev;
		while (tmp && tmp->type == 'W')
			tmp = tmp->prev;
		lex = lex->next;
		while (lex && lex->type == 'W')
			lex = lex->next;
		if (!lex || (lex->type == 'P')
			|| !tmp || tmp->type == 'P'
			|| tmp->type == 'I' || tmp->type == 'O'
			|| tmp->type == 'H' || tmp->type == 'A')
		{
			ft_putendl_fd(\
			"minishell: syntax error near unexpected token `|'", 2);
			g_env->exit_status = 2;
			return (2);
		}
	}
	return (0);
}
