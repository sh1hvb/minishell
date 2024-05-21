/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 06:51:09 by smarsi            #+#    #+#             */
/*   Updated: 2024/05/20 12:05:51 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	is_redirection(char *prompt, t_lexer **lex, int *index);
void	is_string(char *prompt, t_lexer **lex, int *index);
void	is_withspace(char *prompt, t_lexer **lex, int *index);
void	is_string(char *prompt, t_lexer **lex, int *index);
void	is_pipe(char *prompt, t_lexer **lex, int *index);
void	is_quotes(char *prompt, t_lexer **lex, int *index);

void	lexer(char *prompt, t_lexer **lex)
{	
	int	i;
	int	flag[2];

	flag[0] = 0;
	flag[1] = 0;
	i = 0;
	while (prompt[i])
	{
		if (in_delimiters(prompt[i], "<>"))
			is_redirection(prompt, lex, &i);
		else if (prompt[i] == '|')
			is_pipe(prompt, lex, &i);
		else if (in_delimiters(prompt[i], " \t\n"))
			is_withspace(prompt, lex, &i);
		else if (prompt[i] == '\'' || prompt[i] == '\"')
			is_quotes(prompt, lex, &i);
		else
			is_string(prompt, lex, &i);
	}
}


// readline  
//  ls " '-la > out" -a > out | << pp >> p < p  ls	l "   	sl" | ls < 
// > |
// "
//


// ----------->  