#include "../minishell.h"



void ft_echo(t_data *data, t_envp *env)
{
    int i = 1;
    int flag = 0;
    int j = 1;
    (void)env;
    if(data->args[1][0] =='-')
    {
        while(data->args[1][j] == 'n')
            j++;
        if(!(ft_strlen(data->args[1]) - j))
            i = 2 , flag = 0;
        else 
            i = 1 , flag = 1;
    }
    while(data->args[i])
    {
        printf("%s ",data->args[i++]);
    }
    if(flag)
        printf("\n");
}