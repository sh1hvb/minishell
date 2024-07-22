#include "../minishell.h"

static char	*my_strjoin_c(char *s1, char s2)
{
	char	*str;
	int		len;

	if (!s1 && !s2)
		return (NULL);
	else if (!s2)
		return (my_strdup(s1));
	if (!s1)
		len = 2;
	else
		len = (ft_strlen(s1) + 1) + 1;
	str = ft_malloc(len * sizeof(char), 0);
	if (!str)
		return (str);
	str[0] = '\0';
	if (s1)
		ft_strlcat(str, s1, ft_strlen(s1) + 1);
	str[len - 2] = s2;
	str[len - 1] = '\0';
	return (str);
}

static void	string_quotes(t_data *data)
{
	char	*tmp;
	char	delimiter;

	int (i), (j);
	i = 0;
	while (data && data->args && data->args[i])
	{
		tmp = NULL;
		j = 0;
		while (data->args[i][j])
		{
			if ((data->args[i][j] == '\"' || data->args[i][j] == '\''))
			{
				delimiter = data->args[i][j];
				j++;
				while (data->args[i][j] && data->args[i][j] != delimiter)
					tmp = my_strjoin_c(tmp, data->args[i][j++]);
				if (data->args[i][j] == delimiter)
					j++;
			}
			else
				tmp = my_strjoin_c(tmp, data->args[i][j++]);
		}
		if (!tmp)
			data->args[i++] = my_strdup("");
		else
			data->args[i++] = tmp;
	}
}

static void	rmv_file_qts(t_files *data)
{
	char	*tmp;
	char	delimiter;

	int (i);
	while (data && data->delimiter)
	{
		i = 0;
		tmp = NULL;
		while (data->delimiter[i])
		{
			if (data->delimiter[i] == '\"' || data->delimiter[i] == '\'')
			{
				delimiter = data->delimiter[i++];
				while (data->delimiter[i] && data->delimiter[i] != delimiter)
					tmp = my_strjoin_c(tmp, data->delimiter[i++]);
				if (data->delimiter[i] == delimiter)
					i++;
			}
			else
				tmp = my_strjoin_c(tmp, data->delimiter[i++]);
		}
		if (!tmp)
			data->delimiter = my_strdup("");
		else
			data->delimiter = tmp;
		data = data->next;
	}
}

void	remove_quotes(t_data *data_tmp)
{
	string_quotes(data_tmp);
	rmv_file_qts(data_tmp->append);
	rmv_file_qts(data_tmp->heredoc);
	rmv_file_qts(data_tmp->redir_in);
	rmv_file_qts(data_tmp->redir_out);
}
