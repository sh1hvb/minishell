/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 19:05:22 by mchihab           #+#    #+#             */
/*   Updated: 2024/07/28 20:18:10 by mchihab          ###   ########.fr       */
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
		if (!current->value)
			printf("%s\n", current->key);
		else
			printf("%s=\"%s\"\n", current->key, current->value);
	}
}

void	print_env(t_envp *current)
{
	if (current->value)
		printf("%s=%s\n", current->key, current->value);
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
			if (current->flag == 0 && !current->value)
			{
				current = current->next;
				continue ;
			}
			print_env(current);
		}
		current = current->next;
	}
}
