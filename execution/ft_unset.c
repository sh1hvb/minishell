#include "../minishell.h"


void	ft_unset(t_data *data)
{
	int		i;
	t_envp	*head;
	t_envp	*tmp;

	i = 1;
	while (data->args[i])
	{
		head = env;
		while (head)
		{
			if (!ft_strcmp(data->args[i], head->key))
			{
				if (!head->prev)
				{
					env = head->next;
					if (env)
						env->prev = NULL;
				}
				else
				{
					head->prev->next = head->next;
					if (head->next)
						head->next->prev = head->prev;
				}
				free(head->key);
				free(head->value);
				tmp = head;
				head = head->next;
				free(tmp);
				break ;
			}
			else
			{
				head = head->next;
			}
		}
		i++;
	}
}
