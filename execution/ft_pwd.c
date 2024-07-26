#include "../minishell.h"

void	ft_pwd(t_data *data)
{
	static char	*buf;

	(void)data;
	buf = getcwd(NULL, PATH_MAX);
	if (!buf)
	{
		buf = my_get_env(env, "PWD");
		if (!buf)
		{
			printf("\n");
			return ;
		}
		printf("%s\n", buf);
		free(buf);
		return ;
	}
	printf("%s\n", buf);
	free(buf);
}
