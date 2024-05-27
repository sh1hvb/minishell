
#include "../../minishell.h"

int	heredoc_lstsize(t_files *lst)
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

t_files	*heredoc_lstlast(t_files *lst)
{
	int	last;

	last = heredoc_lstsize(lst);
	while (last-- > 1)
		lst = lst->next;
	return (lst);
}


t_files	*heredoc_lstnew(char *value)
{
	t_files	*head;

	head = ft_malloc(sizeof(t_files), 0);
	if (!head)
		return (NULL);
	head->buffer = NULL;
	head->delimiter = my_strdup(value);
    head->index = 0;
	head->next = NULL;
	head->prev = NULL;
	return (head);
}

void	heredoc_lstadd_back(t_files **lst, t_files *new)
{
	t_files	*head;

	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = ft_malloc(sizeof(t_files), 0);
		*lst = new;
	}
	else
	{
		head = heredoc_lstlast(*lst);
		new->prev = head;
        new->index = head->index + 1;
		head->next = new;
	}
}
