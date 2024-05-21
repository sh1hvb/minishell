#include "../minishell.h"

void handle_env(t_envp **env , char *envp[])
{
	char *p;
	char *tmp;

	p = NULL;
	tmp = NULL;
	char **new_env = NULL;
	if(!envp)
	{
		p = ft_strjoin(getenv("PWD"),getenv("SHLVL"));
		tmp = ft_strjoin(p , getenv("_"));
		new_env = ft_split(tmp , '\n');
		free(p);
		free(tmp);
		*env = get_env(new_env);
		ft_freed(new_env);
	}
	else
		*env = get_env(envp);
}

void	ft_lstclear_env(t_envp **lst)
{
	t_envp *next;

	if (!lst)
		return ;
	while (*lst)
	{
		next = (*lst)->next;
        if (*lst)
	    {
            free((*lst)->key);
            free((*lst)->value);
            free(*lst);
            *lst = NULL;
	    }
		*lst = next;
	}
}

t_envp *get_env(char **env)
{
    char **splited;
    t_envp *env_list = NULL;
    t_envp *current = NULL;
    t_envp *new_node;
    int i = 0;
    while (env[i])
    {
        splited = ft_split(env[i], '=');
        new_node = (t_envp *)malloc(sizeof(t_envp));
        if (!new_node)
            return 0;
        new_node->key = ft_strdup(splited[0]);
        new_node->value = ft_strdup(getenv(splited[0]));
        new_node->next = NULL;
        new_node->prev = current;
        if (current)
            current->next = new_node;
        else
            env_list = new_node;
        current = new_node;
        ft_freed(splited);
        i++;
    }
    return env_list;
}
