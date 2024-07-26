/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 20:20:15 by mchihab           #+#    #+#             */
/*   Updated: 2024/07/26 20:20:16 by mchihab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(t_data *data)
{
	static char	*buf;

	(void)data;
	buf = getcwd(NULL, PATH_MAX);
	if (!buf)
	{
		buf = my_get_env(env, "PWD");
		if (!buf)
		{
			printf("\n");
			return ;
		}
		printf("%s\n", buf);
		free(buf);
		return ;
	}
	printf("%s\n", buf);
	free(buf);
}
