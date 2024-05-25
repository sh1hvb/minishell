#include "../minishell.h"

t_data	*pars_lstnew(char *value, int quotes);
void	pars_lstadd_back(t_data **lst, t_data *new);
void	heredoc_lstadd_back(t_herdoc **lst, t_herdoc *new);
t_herdoc	*heredoc_lstnew(char *value);
t_herdoc	*heredoc_lstlast(t_herdoc *lst);

void	pars_in_out(t_data **data, t_lexer **lex, int flag)
{
	*lex = (*lex)->next;
	while (*lex)
	{
		if ((*lex)->type == 'W' && (*lex)->in_quotes == 0)
			return ;
		if (flag)
			(*data)->redir_in = my_strjoin((*data)->redir_in, (*lex)->value);
		else
			(*data)->redir_out = my_strjoin((*data)->redir_in, (*lex)->value);
		*lex = (*lex)->next;
	}
}

void	pars_heredoc(t_data **data, t_lexer **lex)
{
	t_herdoc	*tmp;
	t_herdoc	**head;

	head = &(*data)->heredoc_head;
	*lex = (*lex)->next;
	tmp = heredoc_lstnew((*lex)->value);
	heredoc_lstadd_back(head, tmp);
	*lex = (*lex)->next;
	while (*lex)
	{
		if ((*lex)->type == 'W' && (*lex)->in_quotes == 0)
			return ;
		heredoc_lstlast(*head)->delimiter = my_strjoin((*head)->delimiter, (*lex)->value);
		*lex = (*lex)->next;
	}
}

void	parsing(char *prompt, t_lexer **lex, t_data	**data)
{
	t_lexer	*lex_tmp;
	t_data	*data_tmp;
	t_data	*tmp;
	int		i;

	i = 0;
	lex_tmp = *lex;
	data_tmp = *data;
	(void) prompt;
	while (lex_tmp)
	{
		if (lex_tmp->type == 'I' && !lex_tmp->in_quotes)
			pars_in_out(&data_tmp, &lex_tmp, 1);
		else if (lex_tmp->type == 'O' && !lex_tmp->in_quotes)
			pars_in_out(&data_tmp, &lex_tmp, 0);
		else if (lex_tmp->type == 'H' && !lex_tmp->in_quotes)
			pars_heredoc(&data_tmp, &lex_tmp);
		else if (lex_tmp->value[0] == '|' && !lex_tmp->in_quotes)
		{
			tmp = pars_lstnew(NULL, lex_tmp->in_quotes);
			pars_lstadd_back(&data_tmp, tmp);
			if (!data_tmp->next)
			{
				ft_malloc(0, 1);
				exit(1);
			}
			data_tmp = data_tmp->next;
			i = 0;
		}
		else
		{
			if (lex_tmp->value)
			{
				data_tmp->cmd = my_strjoin(data_tmp->cmd, lex_tmp->value);
				data_tmp->in_quotes = lex_tmp->in_quotes;
			}
		}
		if (lex_tmp)
			lex_tmp = lex_tmp->next;
	}
}
