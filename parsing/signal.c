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
		exit(env->exit_status);
	}
}

void	signal_quit(int sig)
{
	printf("Quit: (core dumped)\n");
	env->exit_status = 131;
	(void)sig;
}

void	sig_quit_heredoc(int sig)
{
	write(0, "", 0);
	
	env->exit_status = 131;
	return ;
	(void)sig;
}
