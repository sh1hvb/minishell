/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 17:59:16 by smarsi            #+#    #+#             */
/*   Updated: 2024/07/28 18:31:49 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_syntax(t_lexer *lex)
{
	while (lex)
	{
		if (lex->type == 'P' && lex->in_quotes == 0 && pipe_syntax(lex))
			return (2);
		if ((lex->type == 'H' || lex->type == 'A' || lex->type == 'I'
				|| lex->type == 'O')
			&& lex->in_quotes == 0 && files_syntax(lex))
			return (2);
		lex = lex->next;
	}
	return (0);
}
