#include "../../minishell.h"

void	call_here_put(t_data *p, int fds)
{
	signal(SIGINT, sigint_heredoc);
	while (p)
	{
		while (p->heredoc)
		{
			heredoc_read_and_put_mult(p, fds);
			p->heredoc = p->heredoc->next;
		}
		p = p->next;
	}
	ft_malloc(0, 1);
	ft_lstclear_env(env);
	exit(0);
}
void	err(void)
{
	printf("error\n");
	ft_malloc(0, 1);
	ft_lstclear_env(env);
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
	t_data *p;

	p = data;
	while (p)
	{
		if (check_heredoc(p))
			return (1);
		p = p->next;
	}
	return (0);
}