#include "../minishell.h"

int	ft_error(char *msg, int ext)
{
	printf("%s\n", msg);
	return (ext);
}

void	ft_freed(char **p)
{
	int	i;

	i = 0;
	while (p[i])
	{
		free(p[i]);
		p[i++] = NULL;
	}
	free(p);
	p = NULL;
}
