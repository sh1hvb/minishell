#include "../minishell.h"


static	int		nb_args(char **args)
{
	int		size;

	size = 0;
	while (args[size])
		size++;
	return (size);
}
void ft_echo(t_data *data, t_envp *env)
{
    int		i;
	int		n_option;

	i = 1;
	n_option = 0;
    if (nb_args(data->args) > 1)
	{
		while (data->args[i] && ft_strcmp(data->args[i], "-n") == 0)
		{
			n_option = 1;
			i++;
		}
		while (data->args[i])
		{
			ft_putstr_fd(data->args[i], 1);
			if (data->args[i + 1] && data->args[i][0] != '\0')
				write(1, " ", 1);
			i++;
		}
	}
    else if (data->args && !data->args[1])
        env->exit_status = 0;
   if (n_option == 0)
		write(1, "\n", 1);
}
