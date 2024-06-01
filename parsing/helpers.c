#include "../minishell.h"

void	initialize_cmd(t_data *data_tmp)
{
	if (!data_tmp->args)
	{
		data_tmp->cmd = NULL;
		data_tmp->args = NULL;
	}
	else
		data_tmp->cmd = data_tmp->args[0];
}

void	helpers_lines(t_data **data, t_files ***head, int flag, char *name)
{
	if (flag == 0)
		(*head) = &(*data)->redir_out;
	else if (flag == 1)
		(*head) = &(*data)->redir_in;
	else if (flag == 2)
		(*head) = &(*data)->heredoc;
	else if (flag == 3)
		(*head) = &(*data)->append;
	if (!name)
		name = my_strdup("");
}

