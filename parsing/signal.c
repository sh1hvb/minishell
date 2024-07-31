/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 17:58:34 by smarsi            #+#    #+#             */
/*   Updated: 2024/07/30 15:50:18 by mchihab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_env->exit_status = 130;
	}
}

void	sigint_int(int sig)
{
	(void)sig;
	printf("\n");
}

void	sigint_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		ft_lstclear_env(g_env);
		ft_malloc(0, 1);
		exit(130);
	}
}

void	signal_quit(int sig)
{
	printf("Quit: (core dumped)\n");
	g_env->exit_status = 131;
	(void)sig;
}

void	sig_quit_heredoc(int sig)
{
	rl_replace_line("", 0);
	g_env->exit_status = 131;
	return ;
	(void)sig;
}
