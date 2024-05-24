
#include "../../minishell.h"

void	pars_lstadd_front(t_data **lst, t_data *new)
{
	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		new->next = NULL;
	}
	else
	{
		new->next = *lst;
		*lst = new;
	}
}
