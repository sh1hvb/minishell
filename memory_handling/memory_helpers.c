
#include "../minishell.h"

int	free_lstsize(t_leaks *lst)
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

t_leaks	*free_lstlast(t_leaks *lst)
{
	int	last;

	last = free_lstsize(lst);
	while (last-- > 1)
		lst = lst->next;
	return (lst);
}
