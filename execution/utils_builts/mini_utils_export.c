#include "../../minishell.h"

int	ascending(int a, int b)
{
	return (a <= b);
}

int	if_flag(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			return (1);
		i++;
	}
	return (0);
}
int	check_equal(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
		{
			return (1);
		}
		i++;
	}
	return (0);
}
void	handle_no_arguments(t_envp *env)
{
	env = sort_list(env, ascending);
	print_env_list("ex");
}
int	handle_no_first_element(char **arr)
{
	if (!arr[0])
	{
		ft_freed(arr);
		return (1);
	}
	return (0);
}