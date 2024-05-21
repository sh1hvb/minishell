
#include "../minishell.h"

void	ft_error(char *msg, int ext)
{
	printf("%s", msg);
	exit(ext);
}

void ft_freed(char **p)
{
	int i = 0;
	while(p[i])
	{
		free(p[i++]);
	}
	free(p);
}
