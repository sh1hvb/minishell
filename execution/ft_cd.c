#include "../minishell.h"

void ft_cd(t_data *data, t_envp *env)
{

    (void)env;
    if(!access(data->args[1], F_OK))
    {
        if(chdir(data->args[1]) == -1 )
            dprintf(2,"path not found");
        printf("%s",data->args[1]);
    }
    dprintf(2,"path not found\n");

}