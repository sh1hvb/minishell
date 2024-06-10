#include "../minishell.h"
int		is_heredoc(t_lexer *lst);
int		heredoc_lstsize(t_files *lst);
t_data	*pars_lstnew(char *value, int quotes);
void	pars_lstadd_back(t_data **lst, t_data *new);
void	heredoc_lstadd_back(t_files **lst, t_files *new);
t_files	*heredoc_lstnew(char *value);
t_files	*heredoc_lstlast(t_files *lst);

static int	is_valid_type(t_lexer *lex)
{
	if ((lex && lex->type == 'W' && lex->in_quotes == 0)
		|| (lex->type != 'S' && (lex->type != '$') && (lex->type != 'W')
			&& lex->type != '\"' && lex->type != '\'')
		|| lex->type == '|')
		return (1);
	return (0);
}

void	pars_files(t_data **data, t_lexer **lex, int flag)
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
		if ((*lex)->value)
			file_name = my_strjoin(file_name, (*lex)->value);
		*lex = (*lex)->next;
	}
	helpers_lines(data, &head, flag, file_name);
	tmp = heredoc_lstnew(file_name);
	tmp->type = 0;
	if (file_name[0] == '\'' || file_name[0] == '\"')
		tmp->type = 1;
	heredoc_lstadd_back(head, tmp);
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
		exit(1);
	}
	if (*data)
		*data = (*data)->next;
	if (*lex)
		*lex = (*lex)->next;
}

void	fill_args(t_lexer **lex, t_data	**data)
{
	t_lexer	*lex_tmp;
	t_data	*data_tmp;

	lex_tmp = *lex;
	data_tmp = *data;
	data_tmp->cmd = my_strjoin(data_tmp->cmd, lex_tmp->value);
	data_tmp->args = lexer_split(data_tmp->cmd, " \t\n");
	data_tmp->in_quotes = lex_tmp->in_quotes;
	if (*lex)
		*lex = (*lex)->next;
}

void	parsing(t_lexer **lex, t_data	**data)
{
	t_lexer	*lex_tmp;
	t_data	*data_tmp;

	lex_tmp = *lex;
	data_tmp = *data;
	while (lex_tmp)
	{
		if (lex_tmp->type == 'I' && !lex_tmp->in_quotes)
			pars_files(&data_tmp, &lex_tmp, 1);
		else if (lex_tmp->type == 'O' && !lex_tmp->in_quotes)
			pars_files(&data_tmp, &lex_tmp, 0);
		else if (lex_tmp->type == 'H' && !lex_tmp->in_quotes)
			pars_files(&data_tmp, &lex_tmp, 2);
		else if (lex_tmp->type == 'A' && !lex_tmp->in_quotes)
			pars_files(&data_tmp, &lex_tmp, 3);
		else if (lex_tmp->type == 'P' && !lex_tmp->in_quotes)
		{
			if (data_tmp->args && data_tmp->args[0])
				data_tmp->cmd = data_tmp->args[0];
			else
				data_tmp->cmd = NULL;
			new_node(&lex_tmp, &data_tmp);
		}
		else
			fill_args(&lex_tmp, &data_tmp);
		remove_quotes(data_tmp);
	}
	initialize_cmd(data_tmp);
	return ;
}
