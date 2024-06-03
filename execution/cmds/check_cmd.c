#include "../../minishell.h"

char **list_to_pointer()
{
	int i = 0;
	char **arr = NULL;
	char *tmp;
	tmp = NULL;
	int size = ft_lstsize_env(env);
	arr = malloc((size + 1) * sizeof(char *));
	if(!arr)
		return NULL;
	while(env)
	{
		tmp = ft_strjoin(env->key,"=");
		arr[i] = ft_strjoin(tmp,env->value);
		// free(tmp);
		i++;
		env = env->next;
	}
	arr[i] = NULL;
	return arr;
}
//-------------------------------------new execution------------------------------------- //
void inc_shell() {
    int tmp;
    t_envp *tmpenv = env;

    while (tmpenv) {
        if (!ft_strcmp(tmpenv->key, "SHLVL")) {
            tmp = ft_atoi(tmpenv->value) + 1;
            free(tmpenv->value);
            tmpenv->value = ft_itoa(tmp);
			break;
        }
        tmpenv = tmpenv->next;
    }
}
void dec_shell() {
    int tmp;
    t_envp *tmpenv = env;

    while (tmpenv) {
        if (!ft_strcmp(tmpenv->key, "SHLVL")) {
            tmp = ft_atoi(tmpenv->value) - 1;
            free(tmpenv->value);
            tmpenv->value = ft_itoa(tmp);
			break;
        }
        tmpenv = tmpenv->next;
    }
}

void process_cmd(t_data *data)
{
	dup2(0, 200);
	if (data && data->next)
		process_pipe(data);
	else
	{
		execute_single_cmd(data);
		// close(data->redir_in->index);
		// close(data->redir_out->index);
	}
	dup2(200,0);
}