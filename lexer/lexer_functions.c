/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 06:28:24 by smarsi            #+#    #+#             */
/*   Updated: 2024/05/20 14:32:07 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	is_withspace(char *prompt, t_lexer **lex, int *index)
{
	t_lexer *new;
	char	*value;
	int		i;

	new = NULL;
	if (!prompt || !lex || !index)
        return;
	i = *index;
	lexer_strchr(prompt, " \t", index, 1);
	value = ft_malloc(*index - i + 1, 0);
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

	new = NULL;
	if (!prompt || !lex || !index)
        return;
	i = *index;
	lexer_strchr(prompt, " \t<>|\n", index, 0);
	value = ft_malloc(*index - i + 1, 0);
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

	new = NULL;
	if (!prompt || !lex || !index)
        return;
	i = *index;
	(*index)++;
	if (prompt[i] == '\'')
		lexer_strchr(prompt, "\'", index, 0);
	else
		lexer_strchr(prompt, "\"", index, 0);
	(*index)++;
	value = ft_malloc(*index - i + 1, 0);
	if (!value)
		return;
	ft_strlcpy(value, prompt + i, *index - i + 1);
	if (prompt[i] == '\'')
		new = ft_lstnew(value, 'S', 1);
	else
		new = ft_lstnew(value, 'S', 2);
	ft_lstadd_back(lex, new);
}

void	is_pipe(char *prompt, t_lexer **lex, int *index)
{
	t_lexer *new;

	new = NULL;
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

	new = NULL;
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
	else
	{
		new = ft_lstnew(ft_strdup(">"), 'O', 0);
		i++;
	}
	*index = i;
	ft_lstadd_back(lex, new);
}
