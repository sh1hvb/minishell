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
void	sigint_c(int sig)
{
	(void) sig;
	printf("\n");
}

void	signal_s(int sig)
{
	printf("Quit: 3\n");
	(void)sig;
}
