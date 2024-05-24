#include "../minishell.h"

t_data	*pars_lstnew(char *value, int quotes);
void	pars_lstadd_back(t_data **lst, t_data *new);

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
		if (lex_tmp->type == 'I' && lex_tmp->in_quotes == 0)
		{
			lex_tmp = lex_tmp->next;
			(*data)->redir_in = my_strdup(lex_tmp->value);
			(*data)->in_quotes = lex_tmp->in_quotes; 
		}
		else if (lex_tmp->type == 'O' && lex_tmp->in_quotes == 0)
		{
			lex_tmp = lex_tmp->next;
			(*data)->redir_out = my_strdup(lex_tmp->value);
			(*data)->in_quotes = lex_tmp->in_quotes; 
		}
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
			// if (lst->value[0] == '\"' && lst->in_quotes != 2)
			// 	lst->value++;
			// else if (lst->value[0] == '\'' && lst->in_quotes != 1)
			// 	lst->value++;
			if (lex_tmp->value)
			{
				data_tmp->cmd = my_strjoin(data_tmp->cmd, lex_tmp->value);
				data_tmp->in_quotes = lex_tmp->in_quotes;
			}
		}
		lex_tmp = lex_tmp->next;
	}
}
