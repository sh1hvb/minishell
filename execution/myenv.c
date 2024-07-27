/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myenv.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 20:32:07 by mchihab           #+#    #+#             */
/*   Updated: 2024/07/26 20:32:21 by mchihab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			printf("%s\n", current->key);
		else if (!current->value && current->flag == 1 && !ft_strcmp(x, "ex"))
			printf("%s=%s\n", current->key, current->value);
		else
		{
			if (!ft_strcmp(x, "ex"))
				printf("%s=\"%s\"\n", current->key, current->value);
			else
				printf("%s=%s\n", current->key, current->value);
		}
		current = current->next;
	}
}

void	new_env(void)
{
	char	*pwd;
	char	*tmp;
	char	*tmp2;
	char	**new_env;

	pwd = getcwd(NULL, PATH_MAX);
	if (!pwd)
		return ;
	tmp = ft_strjoin("PWD=", (pwd));
	free(pwd);
	if (!tmp)
		return ;
	tmp2 = ft_strjoin(tmp, " _=/usr/bin/env SHLVL=2");
	free(tmp);
	if (!tmp2)
		return ;
	new_env = ft_split(tmp2, ' ');
	free(tmp2);
	if (!new_env)
		return ;
	env = get_env(new_env, 1);
	ft_freed(new_env);
}

void	handle_env(char *envp[])
{
	if (!envp || !envp[0])
		new_env();
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

t_envp	*get_env(char **env, int c)
{
	return (build_env_list(env, c));
}
