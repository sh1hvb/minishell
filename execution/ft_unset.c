#include "../minishell.h"


void ft_unset(t_data *data, t_envp **env)
{
    int i = 1;
    t_envp *head;

    head = *env;
    while (data->args[i])
    {
        while (head)
        {
            if(!ft_strcmp(data->args[i], head->key) )
            {
                head->prev->next = head->next;
                ft_lstdelone_env(head);
                head = *env;
                break;
            }
            head = head->next;
        }
        i++;
    }
}