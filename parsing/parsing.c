#include "../minishell.h"

int	heredoc_lstsize(t_files *lst);
t_data	*pars_lstnew(char *value, int quotes);
void	pars_lstadd_back(t_data **lst, t_data *new);
void	heredoc_lstadd_back(t_files **lst, t_files *new);
t_files	*heredoc_lstnew(char *value);
t_files	*heredoc_lstlast(t_files *lst);

static int	is_valid_Type(t_lexer*lex)
{
	if ((lex->type == 'W' && lex->in_quotes == 0) 
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

	*lex = (*lex)->next;
	head = NULL;
	file_name = NULL;
	while (*lex)
	{
		if (is_valid_Type(*lex))
			break ;
		file_name = my_strjoin(file_name, (*lex)->value);
		*lex = (*lex)->next;
	}
	if (flag == 0)
		head = &(*data)->redir_out;
	else if (flag == 1)
		head = &(*data)->redir_in;
	else if (flag == 2)
		head = &(*data)->heredoc;
	else if (flag == 3)
		head = &(*data)->append;
	tmp = heredoc_lstnew(file_name);
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
	data_tmp = data_tmp->next;
	*lex = (*lex)->next;
}

void	fill_args(t_lexer **lex, t_data	**data)
{
	t_lexer	*lex_tmp;
	t_data	*data_tmp;

	lex_tmp = *lex;
	data_tmp = *data;
	data_tmp->cmd = my_strjoin(data_tmp->cmd, lex_tmp->value);
	data_tmp->args = lexer_split(data_tmp->cmd , " \t\n");
	data_tmp->in_quotes = lex_tmp->in_quotes;
	*lex = (*lex)->next;	
}

void	parsing(char *prompt, t_lexer **lex, t_data	**data)
{
	t_lexer	*lex_tmp;
	t_data	*data_tmp;

	lex_tmp = *lex;
	data_tmp = *data;
	(void) prompt;
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
		else if (lex_tmp->value[0] == '|' && !lex_tmp->in_quotes)
			new_node(&lex_tmp, &data_tmp);
		else
			fill_args(&lex_tmp, &data_tmp);
	}
	data_tmp->cmd = data_tmp->args[0];
	
}
