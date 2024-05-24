
#include "../../minishell.h"

void	pars_lstdelone(t_data *lst)
{
	if (lst)
	{
		free(lst->cmd);
		lst->cmd = NULL;
		free(lst);
		lst = NULL;
	}
}

void	pars_lstclear(t_data **lst)
{
	t_data	*next;

	if (!lst)
		return ;
	while (*lst)
	{
		next = (*lst)->next;
		pars_lstdelone(*lst);
		*lst = next;
	}
}
