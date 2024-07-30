/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 12:21:45 by smarsi            #+#    #+#             */
/*   Updated: 2024/07/30 19:26:51 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	rmv_s_qts(char **str)
{
	char	*tmp;
	int		i;

	i = 0;
	(*str)++;
	tmp = *str;
	while (tmp[i])
	{
		if (tmp[i] == '\'')
		{
			tmp[i] = '\0';
			break ;
		}
		i++;
	}
}

void	rmv_d_qts(char **str)
{
	char	*tmp;
	int		i;

	i = 0;
	(*str)++;
	tmp = *str;
	while (tmp[i])
	{
		if (tmp[i] == '\"')
		{
			tmp[i] = '\0';
			break ;
		}
		i++;
	}
}

void	expand_helper(t_lexer *lst, char *tmp)
{
	if (lst->value[0] == '?')
		lst->value = my_strjoin2(ft_itoa(g_env->exit_status), lst->value + 1);
	else
	{
		tmp = my_get_env(g_env, lst->value);
		lst->value = my_strdup(tmp);
		free(tmp);
	}
}

void	expand(char *prompt, t_lexer **lex)
{
	t_lexer	*lst;
	char	*tmp;

	tmp = NULL;
	lst = *lex;
	(void)prompt;
	while (lst)
	{
		if (lst->value[0] == '$' && lst->in_quotes != 2 && ((lst->value[0] == '$') || (!is_heredoc(lst)
			&& (lst->value[1] || (lst->next && lst->in_quotes == 0
					&& (lst->next->value[0] == '\"'
						|| lst->next->value[0] == '\''))))))
		{
			lst->value++;
			expand_helper(lst, tmp);
		}
		else if (lst->value[0] == '~' && !lst->in_quotes)
		{
			lst->value++;
			tmp = my_get_env(g_env, "HOME");
			lst->value = my_strjoin(tmp, lst->value);
			free(tmp);
		}
		lst = lst->next;
	}
}
