/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myenv.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 20:32:07 by mchihab           #+#    #+#             */
/*   Updated: 2024/07/28 20:11:33 by mchihab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	tmp2 = ft_strjoin(tmp, " _=/usr/bin/g_env SHLVL=2");
	free(tmp);
	if (!tmp2)
		return ;
	new_env = ft_split(tmp2, ' ');
	free(tmp2);
	if (!new_env)
		return ;
	g_env = get_env(new_env, 1);
	ft_freed(new_env);
}

void	handle_env(char *envp[])
{
	if (!envp || !envp[0])
		new_env();
	else
		g_env = get_env(envp, 0);
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

t_envp	*get_env(char **g_env, int c)
{
	return (build_env_list(g_env, c));
}
