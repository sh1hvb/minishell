/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 20:00:17 by mchihab           #+#    #+#             */
/*   Updated: 2024/08/04 17:25:17 by mchihab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_directory_error(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": Is a directory\n", 2);
	ft_lstclear_env(g_env);
	ft_malloc(0, 1);
	exit(126);
}

char	*check_access_cmd(char **allpath, char *cmd, int i)
{
	char	*exec;
	char	*path_part;

	path_part = ft_strjoin(allpath[i], "/");
	exec = ft_strjoin(path_part, cmd);
	free(path_part);
	if (access(exec, X_OK) == 0)
	{
		ft_freed(allpath);
		return (exec);
	}
	free(exec);
	return (NULL);
}

char	*get_path(char *cmd)
{
	int		i;
	char	**allpath;
	char	*value;

	if (!cmd)
		return (NULL);
	if (!access(cmd, X_OK) || cmd[0] == '/')
		return ((ft_strdup(cmd)));
	value = my_get_env(g_env, "PATH");
	allpath = ft_split(value, ':');
	free(value);
	if (!allpath)
		return (ft_strdup(cmd));
	i = -1;
	while (allpath[++i])
	{
		value = check_access_cmd(allpath, cmd, i);
		if (value)
			return (value);
	}
	ft_freed(allpath);
	return (ft_strdup(cmd));
}

void	safe_dup2(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
	{
		perror("dup2");
		ft_malloc(0, 1);
		ft_lstclear_env(g_env);
		exit(EXIT_FAILURE);
	}
}
