
#include "../minishell.h"

void	print_env_list(char *x)
{
	t_envp	*current;

	current = env;
	while (current)
	{
		if (!ft_strcmp(x, "ex"))
			printf("declare -x ");
		if (!ft_strcmp(x, "en") && current->flag == 0 && !current->value)
		{
			current = current->next;
			continue ;
		}
		else if (!current->value && current->flag == 0 && !ft_strcmp(x, "ex"))
		{
			printf("%s\n", current->key);
		}
		else if (!current->value && current->flag == 1 && !ft_strcmp(x, "ex"))
		{
			// current->value=ft_strdup("\"\"");
			printf("%s=%s\n", current->key, current->value);
		}
		else
		{
			// if(!current->value &&  ft_strcmp(current->value,"\"\""))
			//     current->value=ft_strdup("\"\"");
			if (!ft_strcmp(x, "ex"))
				printf("%s=\"%s\"\n", current->key, current->value);
			else
				printf("%s=%s\n", current->key, current->value);
		}
		current = current->next;
	}
}
void	handle_env(char *envp[])
{
	char	*pwd;
	char	*tmp;
	char	*tmp2;
	char	**new_env;

	pwd = NULL;
	tmp = NULL;
	tmp2 = NULL;
	new_env = NULL;
	if (!envp || !envp[0])
	{
		pwd = getcwd(NULL, PATH_MAX);
		if (!pwd)
		{
			perror("getcwd");
			return ;
		}
		tmp = ft_strjoin("PWD=", (pwd));
		free(pwd);
		if (!tmp)
		{
			perror("ft_strjoin");
			return ;
		}
		tmp2 = ft_strjoin(tmp, " _=/usr/bin/env SHLVL=2");
		free(tmp);
		if (!tmp2)
		{
			perror("ft_strjoin");
			return ;
		}
		new_env = ft_split(tmp2, ' ');
		free(tmp2);
		if (!new_env)
		{
			perror("ft_split");
			return ;
		}
		env = get_env(new_env, 1);
		ft_freed(new_env);
	}
	else
		env = get_env(envp, 0);
}

void	ft_lstclear_env(t_envp *lst)
{
	t_envp	*next;

	if (!lst)
		return ;
	while (lst)
	{
		next = (lst)->next;
		if (lst)
		{
			free((lst)->key);
			free((lst)->value);
			free(lst);
			lst = NULL;
		}
		lst = next;
	}
}
void	ft_env(void)
{
	print_env_list("en");
}
t_envp	*get_env(char **env, int c)
{
	char	**splited;
	t_envp	*env_list;
	t_envp	*current;
	t_envp	*new_node;
	int		i;

	env_list = NULL;
	current = NULL;
	i = 0;
	while (env[i])
	{
		splited = lexer_split(env[i], "+=");
		new_node = malloc(sizeof(t_envp));
		if (!new_node)
			return (0);
		new_node->key = ft_strdup(splited[0]);
		if (c)
			new_node->value = ft_strdup((splited[1]));
		else
			new_node->value = ft_strdup(getenv(splited[0]));
		new_node->next = NULL;
		new_node->flag = 0;
		new_node->signal_heredoc = 0;
		new_node->exit_status = 0;
		new_node->prev = current;
		if (current)
			current->next = new_node;
		else
			env_list = new_node;
		current = new_node;
		i++;
	}
	return (env_list);
}
