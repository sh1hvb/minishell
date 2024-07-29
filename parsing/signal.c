/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 17:58:34 by smarsi            #+#    #+#             */
/*   Updated: 2024/07/29 16:58:30 by smarsi           ###   ########.fr       */
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
		g_env->exit_status = 130;
		exit(g_env->exit_status);
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
