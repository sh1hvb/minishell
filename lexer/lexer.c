/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 06:51:09 by smarsi            #+#    #+#             */
/*   Updated: 2024/05/20 09:36:51 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	is_redirection(char *prompt, t_lexer **lex, int *index);
void	is_string(char *prompt, t_lexer **lex, int *index);
void	is_withspace(char *prompt, t_lexer **lex, int *index);
void	is_string(char *prompt, t_lexer **lex, int *index);
void	is_pipe(char *prompt, t_lexer **lex, int *index);

void	lexer(char *prompt, t_lexer **lex)
{	
	int	i;
	int	j;

	i = 0;
	t_lexer *new = NULL;
	while (prompt[i])
	{
		if (in_delimiters(prompt[i], "<>"))
			is_redirection(prompt, lex, &i);
		else if (prompt[i] == '|')
			is_pipe(prompt, lex, &i);
		else if (in_delimiters(prompt[i], " \t\n"))
			is_withspace(prompt, lex, &i);
		else
			is_string(prompt, lex, &i);
	}
}

void	is_withspace(char *prompt, t_lexer **lex, int *index)
{
	t_lexer *new;
	char	*value;
	int		i;

	if (!prompt || !lex || !index)
        return;
	i = *index;
	lexer_strchr(prompt, " \t", index, 1);
	value = malloc(*index - i + 1);
	if (!value)
		return;
	ft_strlcpy(value, prompt + i, *index - i + 1);
	new = ft_lstnew(value, 'W', 0);
	ft_lstadd_back(lex, new);
}


void	is_string(char *prompt, t_lexer **lex, int *index)
{
	t_lexer *new;
	char	*value;
	int		i;

	if (!prompt || !lex || !index)
        return;
	i = *index;
	lexer_strchr(prompt, " \t<>|\n", index, 0);
	value = malloc(*index - i + 1);
	if (!value)
		return;
	ft_strlcpy(value, prompt + i, *index - i + 1);
	new = ft_lstnew(value, 'S', 0);
	ft_lstadd_back(lex, new);
}

void	is_quotes(char *prompt, t_lexer **lex, int *index)
{
	t_lexer *new;
	char	*value;
	int		i;

	if (!prompt || !lex || !index)
        return;
	i = *index;
	lexer_strchr(prompt, " \t<>|\n", index, 0);
	value = malloc(*index - i + 1);
	if (!value)
		return;
	ft_strlcpy(value, prompt + i, *index - i + 1);
	new = ft_lstnew(value, 'S', 1);
	ft_lstadd_back(lex, new);
}

void	is_pipe(char *prompt, t_lexer **lex, int *index)
{
	t_lexer *new;

	if (!prompt || !lex || !index)
        return;
	new = ft_lstnew("|", 'P', 0);
	(*index)++;
	ft_lstadd_back(lex, new);
}

void	is_redirection(char *prompt, t_lexer **lex, int *index)
{
	t_lexer *new;
	int		i;

	if (!prompt || !lex || !index)
        return;
	i = *index;
	if (prompt[i] == '<' && prompt[i + 1] == '<')
	{
		new = ft_lstnew(ft_strdup("<<"), 'H', 0);
		i += 2;
	}
	else if (prompt[i] == '<')
	{
		new = ft_lstnew(ft_strdup("<"), 'I', 0);
		i++;
	}
	else if (prompt[i] == '>' && prompt[i + 1] == '>')
	{
		new = ft_lstnew(ft_strdup(">>"), 'A', 0);
		i += 2;
	}
	// else if (prompt[i] == '\'' || prompt[i] == '\"')
	else
	{
		new = ft_lstnew(ft_strdup(">"), 'O', 0);
		i++;
	}
	*index = i;
	ft_lstadd_back(lex, new);
}


// readline  
//  ls " '-la > out" -a > out | << pp >> p < p  ls	l "   	sl" | ls < 
// > |
// "
//


// ----------->  