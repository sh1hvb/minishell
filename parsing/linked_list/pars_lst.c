
#include "../../minishell.h"

int	pars_lstsize(t_data *lst)
{
	int	count;

	if (!lst)
		return (0);
	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

t_data	*pars_lstlast(t_data *lst)
{
	int	last;

	last = pars_lstsize(lst);
	while (last-- > 1)
		lst = lst->next;
	return (lst);
}


t_data	*pars_lstnew(char *value, int quotes)
{
	t_data	*head;

	head = ft_malloc(sizeof(t_data), 0);
	if (!head)
		return (NULL);
	head->cmd = value;
	head->args = NULL;
	head->in_quotes = quotes;
	head->redir_in = NULL;
	head->redir_out = NULL;
	head->has_heredoc = 0;
	head->heredoc = NULL;
	head->append = NULL;
	head->next = NULL;
	head->prev = NULL;
	return (head);
}

void	pars_lstadd_back(t_data **lst, t_data *new)
{
	t_data	*head;

	if (!lst)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		head = pars_lstlast(*lst);
		new->prev = head;
		head->next = new;
	}
}
