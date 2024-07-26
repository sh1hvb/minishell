/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 19:09:30 by smarsi            #+#    #+#             */
/*   Updated: 2024/07/26 19:10:14 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd_continue(t_data *data)
{
	char	*msg;

	msg = ft_strjoin("minishell: cd: ", data->args[1]);
	if (!data->args[1] || !ft_strcmp(data->args[1], "--"))
		cd_home(data, msg);
	else if (data->args[1][0] == '-')
		cd_old_pwd(data, msg);
	else
	{
		if (chdir(data->args[1]) == -1)
		{
			if (!ft_strcmp(data->args[1], ".."))
				ft_putendl_fd("minishell : cd: No such file or directory", 2);
			else
				perror(msg);
			env->exit_status = 1;
			free(msg);
			return (1);
		}
		get_old_pwd();
	}
	free(msg);
	return (0);
}

void	cd_old_pwd_continue(char *tmp)
{
	tmp = my_get_env(env, "OLDPWD");
	ft_putstr_fd(tmp, 1);
	ft_putstr_fd("\n", 1);
	get_old_pwd();
	free(tmp);
}
