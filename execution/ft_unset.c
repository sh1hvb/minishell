#include "../minishell.h"


void ft_unset(t_data *data)
{
    int i = 1;
    t_envp *head;

    head = env;
    while (data->args[i])
    {
        while (head)
        {
            if(!ft_strcmp(data->args[i], head->key) )
            {
                if(!head->prev)
                {
                    env = env->next;
                    env->prev = NULL;
                    ft_lstdelone_env(head);
                    break;
                }
                head->prev->next = head->next;
                ft_lstdelone_env(head);
                head = env;
                break;
            }
            head = head->next;
        }
        i++;
    }
}