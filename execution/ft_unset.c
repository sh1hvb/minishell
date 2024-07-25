#include "../minishell.h"

void	ft_unset(t_data *data)
{
	int i = 1;
	t_envp *head;

	head = env;
	while (data->args[i])
	{
		while (head)
		{
			if (!ft_strcmp(data->args[i], head->key))
			{
				if (!head->prev)
				{
					env = env->next;
					env->prev = NULL;
					free(head->key);
					free(head->value);
					free(head);
					break ;
				}
				head->prev->next = head->next;
				free(head->key);
				free(head->value);
				head = env;
				break ;
			}
			head = head->next;
		}
		i++;
	}
}