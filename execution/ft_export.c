#include "../minishell.h"

static int ascending(int a, int b)
{
	return (a <= b);
}
static void swap_nodes(t_envp *a, t_envp *b) 
{
    char *temp_key; 
    char *temp_value;

    temp_key = a->key;
    temp_value = a->value;
    a->key = b->key;
    a->value = b->value;
    b->key = temp_key;
    b->value = temp_value;
}
static void set_previous_pointers(t_envp *lst) 
{
    t_envp *tmp = lst;
    t_envp *prev = NULL;
    while (tmp) 
    {
        tmp->prev = prev;
        prev = tmp;
        tmp = tmp->next;
    }
}

t_envp *sort_list(t_envp *lst, int (*cmp)(int, int))
{
    int swapped;
    t_envp *ptr1;
    t_envp *lptr = NULL;

    if (lst == NULL)
        return NULL;
    swapped = 1;
    while(swapped)
    {
        swapped = 0;
        ptr1 = lst;
        while (ptr1->next != lptr) {
            if (!cmp(ptr1->key[0], ptr1->next->key[0])) 
            {
                swap_nodes(ptr1 ,ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    };
    set_previous_pointers(lst);
    return lst;
}

void ft_export(t_data *data , t_envp *env)
{
    t_envp *tmp_env;
    t_envp *other;
    other = env;
    tmp_env = NULL;
    int i;
    i = 1;
    (void)data;
    if(!data->args[0])
        printf("not good");
    while(data->args[i])
    {
        if((!ft_isdigit(data->args[i][0])) && check_string(data->args[i])) 
            ft_lstadd_back_env(&env ,ft_lstnew_env(data->args[i], env));
        else
            ft_error("bad arguments",1);
        i++;
    }
    tmp_env = sort_list(env , ascending);
    print_env_list(tmp_env);
}

