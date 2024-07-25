#include "../minishell.h"

void	is_withspace(char *prompt, t_lexer **lex, int *index, int flag)
{
	t_lexer	*new;
	char	*value;
	int		i;

	new = NULL;
	if (!prompt || !lex || !index)
		return ;
	i = *index;
	lexer_strchr(prompt, " \t\n", index, 1);
	value = ft_malloc(*index - i + 1, 0);
	if (!value)
		return ;
	ft_strlcpy(value, prompt + i, *index - i + 1);
	new = ft_lstnew(value, 'W', flag);
	ft_lstadd_back(lex, new);
}


void	is_dollar(char *prompt, t_lexer **lex, int *index, int flag)
{
	t_lexer	*new;
	char	*value;
	int		i;

	new = NULL;
	if (!prompt || !lex || !index)
		return ;
	i = *index;
	(*index)++;
	lexer_strchr_d(prompt, " \t\n", index, 0);
	value = ft_malloc(*index - i + 1, 0);
	if (!value)
		return ;
	ft_strlcpy(value, prompt + i, *index - i + 1);
	new = ft_lstnew(value, '$', flag);
	ft_lstadd_back(lex, new);
}

void	is_string(char *prompt, t_lexer **lex, int *index, int flag)
{
	t_lexer	*new;
	char	*value;
	int		i;

	new = NULL;
	if (!prompt || !lex || !index)
		return ;
	i = *index;
	if (in_delimiters(prompt[i], "$+-"))
		(*index)++;
	lexer_strchr(prompt, " \t\n<>|\'\"$+-", index, 0);
	value = ft_malloc(*index - i + 1, 0);
	if (!value)
		return ;
	ft_strlcpy(value, prompt + i, *index - i + 1);
	new = ft_lstnew(value, 'S', flag);
	ft_lstadd_back(lex, new);
}

void	s_quotes(char *prompt, int *index, int flag)
{
	if (flag == 1)
		(*index)++;
	else
	{
		(*index)++;
		lexer_strchr(prompt, "\'", index, 0);
		(*index)++;
	}
}

void	is_quotes(char *prompt, t_lexer **lex, int *index, int flag)
{
	t_lexer	*new;
	char	*value;
	int		i;

	new = NULL;
	if (!prompt || !lex || !index)
		return ;
	i = *index;
	if (prompt[i] == '\'')
		s_quotes(prompt, index, flag);
	else
		(*index)++;
	value = ft_malloc(*index - i + 1, 0);
	if (!value)
		return ;
	ft_strlcpy(value, prompt + i, *index - i + 1);
	if (prompt[i] == '\'')
		new = ft_lstnew(value, '\'', flag);
	else
		new = ft_lstnew(value, '\"', flag);
	ft_lstadd_back(lex, new);
}
