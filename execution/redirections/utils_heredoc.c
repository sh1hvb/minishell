/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 20:07:12 by mchihab           #+#    #+#             */
/*   Updated: 2024/08/01 14:58:53 by mchihab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	call_here_put(t_data *p)
{
	char	*tmp_path;
	int		fds;

	tmp_path = "/tmp/heredo.txt";
	signal(SIGINT, sigint_heredoc);
	while (p)
	{
		while (p->heredoc)
		{
			fds = open(tmp_path, O_CREAT | O_TRUNC | O_WRONLY, 0644);
			if (!fds)
				err();
			heredoc_read_and_put_mult(p, fds);
			p->heredoc = p->heredoc->next;
			close(fds);
		}
		p = p->next;
	}
	ft_malloc(0, 1);
	ft_lstclear_env(g_env);
	exit(0);
}

void	err(void)
{
	printf("error\n");
	ft_malloc(0, 1);
	ft_lstclear_env(g_env);
	exit(0);
}

int	check_heredoc(t_data *data)
{
	t_data	*p;

	p = data;
	if (p->heredoc)
		return (1);
	else
		return (0);
}

int	check_heredoc_two(t_data *data)
{
	t_data	*p;

	p = data;
	while (p)
	{
		if (check_heredoc(p))
			return (1);
		p = p->next;
	}
	return (0);
}
