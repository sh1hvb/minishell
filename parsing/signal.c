#include "../minishell.h"

void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		env->exit_status = 130;
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sigint_int(int sig)
{
	(void) sig;
	printf("\n");
}

void	sigint_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		env->exit_status = 130;
		env->signal_heredoc = 1;
	}
}

void	signal_quit(int sig)
{
	printf("Quit: 3\n");
	env->exit_status = 131;
	(void)sig;
}

void	sig_quit_heredoc(int sig)
{
	env->exit_status = 131;
	write(1, "", 0);
	(void)sig;
}
