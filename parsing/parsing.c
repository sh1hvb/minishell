#include "../minishell.h"

void	parsing(char *prompt, t_lexer **lex)
{
	t_lexer	*lst;
	t_data	*data;
	int		i;

	lst = *lex;
	(void) prompt;
	while (lst)
	{
		if (lst->type == 'I' && lst->in_quotes == 0)
		{
			lst = lst->next;
			data->redir_in = ft_strdup(lst->value);
		}
		lst = lst->next;
	}
}