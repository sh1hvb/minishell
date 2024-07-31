/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_file_args.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:38:23 by smarsi            #+#    #+#             */
/*   Updated: 2024/07/30 20:10:43 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pars_files(t_data **data, t_lexer **lex, int flag)
{
	char	*file_name;
	t_files	*tmp;
	t_files	**head;

	if (*lex)
		*lex = (*lex)->next;
	head = NULL;
	file_name = NULL;
	while (*lex)
	{
		if (is_valid_type(*lex))
			break ;
		if (is_ambiguous(*lex))
			return (1);
		if ((*lex)->value)
			file_name = my_strjoin(file_name, (*lex)->value);
		*lex = (*lex)->next;
	}
	helpers_lines(data, &head, flag, file_name);
	tmp = heredoc_lstnew(file_name);
	tmp->type = 0;
	if ((file_name[0] == '\'' || file_name[0] == '\"'))
		tmp->type = 1;
	heredoc_lstadd_back(head, tmp);
	return (0);
}

void	new_node(t_lexer **lex, t_data	**data)
{
	t_lexer	*lex_tmp;
	t_data	*data_tmp;
	t_data	*tmp;

	lex_tmp = *lex;
	data_tmp = *data;
	tmp = pars_lstnew(NULL, lex_tmp->in_quotes);
	pars_lstadd_back(&data_tmp, tmp);
	if (!data_tmp->next)
	{
		ft_malloc(0, 1);
		exit (1);
	}
	if (*data)
		*data = (*data)->next;
	if (*lex)
		*lex = (*lex)->next;
}

void	fill_args(t_lexer **lex, t_data	**data, int export_flag)
{
	t_lexer	*lex_tmp;
	t_data	*data_tmp;

	if ((*lex)->type == '$' && (*lex)->in_quotes == 0 && export_flag)
	{
		(*lex)->value = my_strjoin("\"", (*lex)->value);
		(*lex)->value = my_strjoin((*lex)->value, "\"");
	}
	lex_tmp = *lex;
	data_tmp = *data;
	data_tmp->cmd = my_strjoin(data_tmp->cmd, lex_tmp->value);
	data_tmp->args = lexer_split(data_tmp->cmd, " \t\n");
	data_tmp->in_quotes = lex_tmp->in_quotes;
	if (*lex)
		*lex = (*lex)->next;
}
