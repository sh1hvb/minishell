#include "../minishell.h"



void ft_echo(t_data *data, t_envp *env)
{
    int i = 1;
    (void)env;
    while(data->args[i])
    {
        printf("%s ",data->args[i++]);
    }
}