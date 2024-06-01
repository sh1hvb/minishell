#include "../../minishell.h"

int	files_syntax(t_lexer *lex)
{
	if (lex)
	{
		lex = lex->next;
		while (lex && lex->type == 'W')
			lex = lex->next;
		if (!lex)
			printf("bash: syntax error near unexpected token `newline'\n");
		else if (lex->type == 'I')
			printf("bash: syntax error near unexpected token `<'\n");
		else if (lex->type == 'O')
			printf("bash: syntax error near unexpected token `>'\n");
		else if (lex->type == 'H')
			printf("bash: syntax error near unexpected token `<<'\n");
		else if (lex->type == 'A')
			printf("bash: syntax error near unexpected token `>>'\n");
		if (!lex || lex->type == 'I' || lex->type == 'O'
			|| lex->type == 'H' || lex->type == 'A')
			return (2);
	}
	return (0);
}
