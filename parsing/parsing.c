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

static int	is_ambiguous(t_lexer *lex)
{
	char	*tmp;
	int		i;

	if (lex && lex->type == '$' && lex->in_quotes == 0)
	{
		i = 0;
		tmp = lex->value;
		while (tmp[i])
		{
			if (tmp[i] <= 32)
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(tmp, 2);
				ft_putendl_fd(": ambiguous redirect", 2);
				env->exit_status = 1;
				return (1);
			}
			i++;
		}
	}
	return (0);
}

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
	if (file_name[0] == '\'' || file_name[0] == '\"')
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

void	check_empty_cmd(t_data	*data_tmp)
{
	int	i;

	i = 0;
	if (data_tmp->args && data_tmp->args[0])
	{
		while (data_tmp->args[0][i] && data_tmp->args[0][i] <= 32)
			i++;
		if (!data_tmp->args[0][i])
			data_tmp->cmd = NULL;
	}
}

static int	is_redirection(t_lexer *lex)
{
	return (lex->type == 'I' || lex->type == 'O'\
	|| lex->type == 'H' || lex->type == 'A');
}

int	parsin_redirection(t_data **data_tmp, t_lexer **lex_tmp)
{
	int	flag;

	flag = 0;
	if ((*lex_tmp)->type)
	{
		if ((*lex_tmp)->type == 'I' && !(*lex_tmp)->in_quotes)
			flag = pars_files(data_tmp, lex_tmp, 1);
		else if ((*lex_tmp)->type == 'O' && !(*lex_tmp)->in_quotes)
			flag = pars_files(data_tmp, lex_tmp, 0);
		else if ((*lex_tmp)->type == 'H' && !(*lex_tmp)->in_quotes)
			flag = pars_files(data_tmp, lex_tmp, 2);
		else if ((*lex_tmp)->type == 'A' && !(*lex_tmp)->in_quotes)
			flag = pars_files(data_tmp, lex_tmp, 3);
		if (flag)
			return (1);
	}
	
	return (0);		
}

int	parsing(t_lexer **lex, t_data	**data)
{
	t_lexer	*lex_tmp;
	t_data	*data_tmp;
	int		export_flag;

	export_flag = 0;
	lex_tmp = *lex;
	data_tmp = *data;
	while (lex_tmp)
	{
		if (!ft_strcmp(lex_tmp->value, "export"))
			export_flag = 1;
		if (!lex_tmp->in_quotes && is_redirection(lex_tmp))
		{
			if (parsin_redirection(&data_tmp, &lex_tmp))
				return (1);
		}
		else if (lex_tmp->type == 'P' && !lex_tmp->in_quotes)
		{
			remove_quotes(data_tmp);
			if (data_tmp->args && data_tmp->args[0])
				data_tmp->cmd = data_tmp->args[0];
			else
				data_tmp->cmd = NULL;
			new_node(&lex_tmp, &data_tmp);
			export_flag = 0;
		}
		else
		{
			if (lex_tmp->type == '$' && lex_tmp->in_quotes == 0 && export_flag)
			{
				lex_tmp->value = my_strjoin("\"", lex_tmp->value);
				lex_tmp->value = my_strjoin(lex_tmp->value, "\"");
			}
			fill_args(&lex_tmp, &data_tmp);
		}
		check_empty_cmd(data_tmp);
	}
	remove_quotes(data_tmp);
	initialize_cmd(data_tmp);
	return (0);
}
