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
		{
			if(s[i] == '+' && s[i + 1] == '=')
            	return 2;
            return 0;
		}
        i++;
    }
    return 1;
    
}
int check_sp(char *s)
{
    int i;
    i = 0;

    while (s[i])
    {
		while(s[i] == 32)
			i++;
		if(s[i] == '=')
			return 1;

        i++;
    }
    return 0;
    
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
void	ft_lstdelone_env(t_envp *lst)
{
	if (lst)
	{
		free(lst->value);
		lst->value = NULL;
		free(lst->key);
		lst->key =NULL;
		free(lst);
		lst = NULL;
	}
}
t_envp	*ft_lstnew_env(char *value, t_envp *env, int flag)
{
	t_envp	*head;
    char **splited;
    t_envp *last;

	splited = NULL;
    last = ft_lstlast_env(env);
    splited = lexer_split(value ,"+=");
	head = malloc(sizeof(t_envp));
	if (!head)
		return (NULL);
    head->key = splited[0];
    head->value = splited[1];
	head->flag = flag;
    head->next = NULL;
	head->prev = last;
	free(splited);
	return (head);
}