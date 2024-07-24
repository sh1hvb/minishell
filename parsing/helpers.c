#include "../minishell.h"

void	initialize_cmd(t_data *data_tmp)
{
	if (!data_tmp->args)
	{
		data_tmp->cmd = NULL;
		data_tmp->args = NULL;
	}
	else
		data_tmp->cmd = data_tmp->args[0];
}

void	helpers_lines(t_data **data, t_files ***head, int flag, char *name)
{
	if (flag == 0)
		(*head) = &(*data)->redir_out;
	else if (flag == 1)
		(*head) = &(*data)->redir_in;
	else if (flag == 2)
		(*head) = &(*data)->heredoc;
	else if (flag == 3)
		(*head) = &(*data)->append;
	if (!name)
		name = my_strdup("");
}

int	is_valid_type(t_lexer *lex)
{
	if ((lex && lex->type == 'W' && lex->in_quotes == 0)
		|| (lex->type != 'S' && (lex->type != '$') && (lex->type != 'W')
			&& lex->type != '\"' && lex->type != '\'')
		|| lex->type == '|')
		return (1);
	return (0);
}

int	is_ambiguous(t_lexer *lex)
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
