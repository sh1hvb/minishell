/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 19:05:22 by mchihab           #+#    #+#             */
/*   Updated: 2024/07/30 19:56:01 by mchihab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_export_command(const char *x)
{
	return (!strcmp(x, "ex"));
}

int	is_env_command(const char *x)
{
	return (!strcmp(x, "en"));
}

void	print_export(t_envp *current)
{
	if (strcmp(current->key, "_"))
	{
		if (!current->value || !current->value[0])
			printf("%s\n", current->key);
		else
		{
			if(!ft_strcmp(current->value,"\"\""))
				printf("%s=%s\n", current->key, current->value);
			else
				printf("%s=\"%s\"\n", current->key, current->value);
		}
	}
}

void	print_env(t_envp *current)
{
	if (current->value )
	{
		if(!ft_strcmp(current->value, "\"\""))
			printf("%s=\n", current->key);
		else
			printf("%s=%s\n", current->key, current->value);
	}
	else
		printf("%s\n", current->key);
}

void	print_env_list(t_envp *a, char *x)
{
	t_envp	*current;

	current = a;
	while (current)
	{
		if (is_export_command(x))
		{
			if (strcmp(current->key, "_"))
				printf("declare -x ");
			print_export(current);
		}
		else if (is_env_command(x))
		{
			if (current->flag == 0 && (!current->value || !current->value[0]))
			{
				current = current->next;
				continue ;
			}
			print_env(current);
		}
		current = current->next;
	}
}
