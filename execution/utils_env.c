/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 20:40:19 by mchihab           #+#    #+#             */
/*   Updated: 2024/07/28 18:06:19 by mchihab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	**list_to_pointer(void)
{
	int		i;
	char	**arr;
	char	*tmp;
	int		size;
	t_envp	*lst;

	lst = g_env;
	i = 0;
	arr = NULL;
	tmp = NULL;
	size = ft_lstsize_env(lst);
	arr = malloc((size + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	while (lst)
	{
		tmp = ft_strjoin(lst->key, "=");
		arr[i] = ft_strjoin(tmp, lst->value);
		free(tmp);
		i++;
		lst = lst->next;
	}
	arr[i] = NULL;
	return (arr);
}

void	inc_shell(void)
{
	int		tmp;
	t_envp	*tmpenv;

	tmpenv = g_env;
	while (tmpenv)
	{
		if (!ft_strcmp(tmpenv->key, "SHLVL"))
		{
			tmp = ft_atoi(tmpenv->value) + 1;
			free(tmpenv->value);
			if (tmp > 1000)
			{
				tmpenv->value = (ft_itoa(1));
				ft_putendl_fd("bash: warning: shell level (1001) too high,\
				 resetting to 1", 2);
			}
			else
				tmpenv->value = (ft_itoa(tmp));
			break ;
		}
		tmpenv = tmpenv->next;
	}
}

int	check_string(char *s)
{
	int	i;

	i = 0;
	if (s[0] == '=')
		return (0);
	while (s[i])
	{
		if (s[i] == '=')
			return (1);
		if (!ft_isalnum(s[i]))
		{
			if (s[i] == '+' && s[i + 1] == '=')
				return (2);
			return (0);
		}
		i++;
	}
	return (1);
}
