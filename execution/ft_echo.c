#include "../minishell.h"

void ft_echo(t_data *data, t_envp *env)
{
    int i = 1;
    int flag = 1;
    int j = 1;
    (void)env;
    if (data->args && data->args[1])
    {
        if(data->args[1][0] == '-')
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
            
            write(1,data->args[i],ft_strlen(data->args[i]));
            i++;
            if (data->args[i])
                printf(" ");
            
        }
    }
    else if (data->args && !data->args[1])
        env->exit_status = 0;
    if(flag)
        printf("\n");
}
