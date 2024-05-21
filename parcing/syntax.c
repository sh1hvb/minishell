/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 06:43:29 by smarsi            #+#    #+#             */
/*   Updated: 2024/05/20 16:22:19 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	valid_prompt(char *prompt)
{
	int (i), (flag), (flag2);
	flag = 0;
	flag2 = 0;
	i = 0;
	while (prompt[i])
	{
		if (prompt[i] == '\"' && !flag2)
		{
			if (flag == 0)
				flag = 1;
			else
				flag = 0;
		}
		else if (prompt[i] == '\'' && !flag)
		{
			if (flag2 == 0)
				flag2 = 1;
			else
				flag2 = 0;
		}
		i++;
	}
	if (flag == 1 || flag2 == 1)
	{
		free(prompt);
		ft_malloc(0, 1);
		ft_error("Syntax Error. \n", 1);
	}
}
