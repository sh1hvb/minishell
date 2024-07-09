#include "../../minishell.h"

int	files_syntax(t_lexer *lex)
{
	if (lex)
	{
		lex = lex->next;
		while (lex && lex->type == 'W')
			lex = lex->next;
		if (!lex)
			ft_putendl_fd("minishell: syntax error near unexpected token `newline'", 2);
		else if (lex->type == 'I')
			ft_putendl_fd("minishell: syntax error near unexpected token `<'", 2);
		else if (lex->type == 'O')
			ft_putendl_fd("minishell: syntax error near unexpected token `>'", 2);
		else if (lex->type == 'H')
			ft_putendl_fd("minishell: syntax error near unexpected token `<<'", 2);
		else if (lex->type == 'A')
			ft_putendl_fd("minishell: syntax error near unexpected token `>>'", 2);
		if (!lex || lex->type == 'I' || lex->type == 'O'
			|| lex->type == 'H' || lex->type == 'A')
		{
			env->exit_status = 2;
			return (2);
		}
	}
	return (0);
}
