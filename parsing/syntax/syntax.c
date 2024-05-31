#include "../../minishell.h"

int	check_syntax(t_lexer *lex)
{
	while (lex)
	{
		if (lex->type == 'P' && lex->in_quotes == 0 && pipe_syntax(lex))
			return (2);
		if ((lex->type == 'H' || lex->type == 'A' || lex->type == 'I' || lex->type == 'O')
		&& lex->in_quotes == 0 && files_syntax(lex))
			return (2);
		lex = lex->next;
	}
	return (0);
}