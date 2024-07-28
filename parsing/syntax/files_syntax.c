/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 17:58:41 by smarsi            #+#    #+#             */
/*   Updated: 2024/07/28 18:06:19 by mchihab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	files_syntax(t_lexer *lex)
{
	char	*msg;

	msg = "minishell: syntax error near unexpected token `newline'";
	if (!lex)
		return (0);
	lex = lex->next;
	while (lex && lex->type == 'W')
		lex = lex->next;
	if (!lex)
		ft_putendl_fd(msg, 2);
	else if (lex->type == 'I')
		ft_putendl_fd(msg, 2);
	else if (lex->type == 'O')
		ft_putendl_fd(msg, 2);
	else if (lex->type == 'H')
		ft_putendl_fd(msg, 2);
	else if (lex->type == 'A')
		ft_putendl_fd(msg, 2);
	if (!lex || lex->type == 'I' || lex->type == 'O'
		|| lex->type == 'H' || lex->type == 'A')
	{
		g_env->exit_status = 2;
		return (2);
	}
	return (0);
}
