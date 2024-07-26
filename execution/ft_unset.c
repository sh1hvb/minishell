#include "../minishell.h"

void	condition(t_envp *head)
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
}
void	remove_node(t_envp *head, t_data *data, int i)
{
	t_envp	*tmp;

	tmp = NULL;
	while (head)
	{
		if (!ft_strcmp(data->args[i], head->key) && ft_strcmp(data->args[i],
				"_"))
		{
			condition(head);
			free(head->key);
			free(head->value);
			tmp = head;
			head = head->next;
			free(tmp);
			break ;
		}
		else
			head = head->next;
	}
}
void	ft_unset(t_data *data)
{
	int		i;
	t_envp	*head;

	i = 1;
	while (data->args[i])
	{
		head = env;
		remove_node(head, data, i);
		i++;
	}
}
