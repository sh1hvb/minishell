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
			ft_putendl_fd("minishell: syntax error \
			near unexpected token `|'", 2);
			env->exit_status = 2;
			return (2);
		}
	}
	return (0);
}
