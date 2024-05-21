#include "../minishell.h"

void	is_redirection(char *prompt, t_lexer **lex, int *index, int flag);
void	is_string(char *prompt, t_lexer **lex, int *index, int flag);
void	is_withspace(char *prompt, t_lexer **lex, int *index, int flag);
void	is_string(char *prompt, t_lexer **lex, int *index, int flag);
void	is_pipe(char *prompt, t_lexer **lex, int *index, int flag);
void	is_quotes(char *prompt, t_lexer **lex, int *index, int flag);
int	in_quotes(char prompt, int *flag_sq, int *flag_dq);

void	lexer(char *prompt, t_lexer **lex)
{	
	int	i;
	int	flag_sq;
	int	flag_dq;
	int	flag;

	flag_sq = 0;
	flag_dq = 0;
	i = 0;
	while (prompt[i])
	{
		flag = in_quotes(prompt[i], &flag_dq, &flag_sq);
		if (in_delimiters(prompt[i], "<>"))
			is_redirection(prompt, lex, &i, flag);
		else if (prompt[i] == '|')
			is_pipe(prompt, lex, &i, flag);
		else if (in_delimiters(prompt[i], " \t\n"))
			is_withspace(prompt, lex, &i, flag);
		else if (prompt[i] == '\'' || prompt[i] == '\"')
			is_quotes(prompt, lex, &i, flag);
		else if (prompt[i] ==  '$')
			is_dollar(prompt, lex, &i, flag);
		else
			is_string(prompt, lex, &i, flag);
	}
}


// readline  
//  ls " '-la > out" -a > out | << pp >> p < p  ls	l "   	sl" | ls < 
// > |
// "
//


// ----------->  