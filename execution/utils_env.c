#include "../minishell.h"

void	ft_lstadd_back_env(t_envp **lst, t_envp *new)
{
	t_envp	*head;

	if (!lst)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		head = ft_lstlast_env(*lst);
		head->next = new;
	}
}
int check_string(char *s)
{
    int i;
    i = 0;
    if(s[0]=='=')
        return 0;
    while (s[i])
    {
        if(s[i]=='=')
            return 1;
        if(!ft_isalnum(s[i]))
            return 0;
        i++;
    }
    return 1;
    
}
int	ft_lstsize_env(t_envp *lst)
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
void	ft_lstadd_front_env(t_envp **lst, t_envp *new)
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
t_envp	*ft_lstlast_env(t_envp *lst)
{
	int	last;
	last = ft_lstsize_env(lst);
	while (last-- > 1)
		lst = lst->next;
	return (lst);
}
t_envp	*ft_lstnew_env(char *value, t_envp *env)
{
	t_envp	*head;
    char **splited;
    t_envp *last;
    last = ft_lstlast_env(env);
    splited = ft_split(value ,'=');
	head = malloc(sizeof(t_envp));
	if (!head)
		return (NULL);
    head->key = splited[0];
    head->value = splited[1];
    head->next = NULL;
	head->prev = last;
	return (head);
}