/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_functions2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 12:20:38 by smarsi            #+#    #+#             */
/*   Updated: 2024/07/27 12:20:41 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	in_delimiters(char target, char *delimiters)
{
	int	i;

	i = 0;
	while (delimiters[i])
	{
		if (target == delimiters[i])
			return (1);
		i++;
	}
	return (0);
}

void	is_pipe(char *prompt, t_lexer **lex, int *index, int flag)
{
	t_lexer	*new;	

	new = NULL;
	if (!prompt || !lex || !index)
		return ;
	new = ft_lstnew("|", 'P', flag);
	(*index)++;
	if (!flag)
		lexer_strchr(prompt, " \t\n", index, 1);
	ft_lstadd_back(lex, new);
}

void	is_redirection_helper(char *prompt, t_lexer **new, int *index, int flag)
{
	int	i;

	i = *index;
	if (prompt[i + 1] == '>')
	{
		*new = ft_lstnew(my_strdup(">>"), 'A', flag);
		i += 2;
	}
	else
	{
		*new = ft_lstnew(my_strdup(">"), 'O', flag);
		i++;
	}
	*index = i;
}

void	is_redirection(char *prompt, t_lexer **lex, int *index, int flag)
{
	t_lexer	*new;
	int		i;

	new = NULL;
	if (!prompt || !lex || !index)
		return ;
	i = *index;
	if (prompt[i] == '<' && prompt[i + 1] == '<')
	{
		new = ft_lstnew(my_strdup("<<"), 'H', flag);
		i += 2;
	}
	else if (prompt[i] == '<')
	{
		new = ft_lstnew(my_strdup("<"), 'I', flag);
		i++;
	}
	else if (prompt[i] == '>')
		is_redirection_helper(prompt, &new, &i, flag);
	*index = i;
	if (!flag)
		lexer_strchr(prompt, " \t\n", index, 1);
	ft_lstadd_back(lex, new);
}
