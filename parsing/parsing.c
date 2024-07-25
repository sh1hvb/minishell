#include "../minishell.h"

static void	check_empty_cmd(t_data	*data_tmp)
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

static int	parsin_redirection(t_data **data_tmp, t_lexer **lex_tmp)
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

static void	parsin_pipe(t_data **data_tmp, t_lexer **lex_tmp, int *export_flag)
{
	if ((*lex_tmp)->type)
	{
		remove_quotes(*data_tmp);
		if ((*data_tmp)->args && (*data_tmp)->args[0])
			(*data_tmp)->cmd = (*data_tmp)->args[0];
		else
			(*data_tmp)->cmd = NULL;
		new_node(lex_tmp, data_tmp);
	}
	export_flag = 0;
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
			parsin_pipe(&data_tmp, &lex_tmp, &export_flag);
		else
			fill_args(&lex_tmp, &data_tmp, export_flag);
		check_empty_cmd(data_tmp);
	}
	remove_quotes(data_tmp);
	initialize_cmd(data_tmp);
	return (0);
}
