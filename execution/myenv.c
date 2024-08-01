/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myenv.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 20:32:07 by mchihab           #+#    #+#             */
/*   Updated: 2024/08/01 17:16:57 by mchihab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	clean_plus_from_key(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == '+')
			return (1);
		i++;
	}
	return (0);
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
	{
		new_env();
		move_key_to_end("_");
	}
	else
	{
		g_env = get_env(envp, 0);
		move_key_to_end("_");
	}
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
