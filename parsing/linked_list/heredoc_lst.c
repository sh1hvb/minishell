
#include "../../minishell.h"

int	heredoc_lstsize(t_herdoc *lst)
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

t_herdoc	*heredoc_lstlast(t_herdoc *lst)
{
	int	last;

	last = heredoc_lstsize(lst);
	while (last-- > 1)
		lst = lst->next;
	return (lst);
}


t_herdoc	*heredoc_lstnew(char *value)
{
	t_herdoc	*head;

	head = ft_malloc(sizeof(t_herdoc), 0);
	if (!head)
		return (NULL);
	head->buffer = NULL;
	head->delimiter = my_strdup(value);
    head->heredocs_index = 0;
	head->next = NULL;
	head->prev = NULL;
	return (head);
}

void	heredoc_lstadd_back(t_herdoc **lst, t_herdoc *new)
{
	t_herdoc	*head;

	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = ft_malloc(sizeof(t_herdoc), 0);
		*lst = new;
	}
	else
	{
		head = heredoc_lstlast(*lst);
		new->prev = head;
        new->heredocs_index = head->heredocs_index + 1;
		head->next = new;
	}
}
