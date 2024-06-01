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

char	*my_strjoin_c(char *s1, char s2)
{
	char	*str;
	int		len;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
	{
		str = malloc(2);
		str[0] = s2;
		str[1] = '\0';
		return (str);
	}
	else if (!s2)
		return (my_strdup(s1));
	len = (ft_strlen(s1) + 1) + 1;
	str = ft_malloc(len * sizeof(char), 0);
	if (!str)
		return (str);
	str[0] = '\0';
	ft_strlcat(str, s1, ft_strlen(s1) + 1);
	str[len - 2] = s2;
	str[len - 1] = '\0';
	return (str);
}

void	remove_quotes(t_data *data)
{
	char	*tmp;
	char	delimiter;

	int (i), (j);	
	i = 0;
	if (data && data->args)
	{
		while (data->args[i])
        {
			tmp = NULL;
            j = 0;
			while (data->args[i][j])
			{
				if (data->args[i][j] == '\"' || data->args[i][j] == '\'')
				{
					delimiter = data->args[i][j];
					j++;
					while (data->args[i][j] && data->args[i][j] != delimiter)
					{
						tmp = my_strjoin_c(tmp, data->args[i][j]);
						j++;
					}
					if (data->args[i][j] == delimiter)
						j++;
				}
				else
				{
					tmp = my_strjoin_c(tmp, data->args[i][j]);
					j++;
				}
			}
			data->args[i] = tmp;
			i++;
        }
	}
}
