#include "../minishell.h"

void	rmv_s_qts(char **str)
{
	char	*tmp;
	int		i;

	i = 0;
	(*str)++;
	tmp = *str;
	while (tmp[i])
	{
		if (tmp[i] == '\'')
		{
			tmp[i] = '\0';
			break ;
		}
		i++;
	}
}

void	rmv_d_qts(char **str)
{
	char	*tmp;
	int		i;

	i = 0;
	(*str)++;
	tmp = *str;
	while (tmp[i])
	{
		if (tmp[i] == '\"')
		{
			tmp[i] = '\0';
			break ;
		}
		i++;
	}
}

int	is_heredoc(t_lexer *lst)
{
	char	delimiter;

	if (lst && lst->prev && lst->prev->type == 'H')
		return (1);
	if (lst && lst->in_quotes)
	{
		delimiter = '\"';
		if (lst->type == '\'')
			delimiter = '\'';
		printf("before %c\n", delimiter);
		while (lst && lst->value[0] != delimiter)
			lst = lst->prev;
		if (lst && lst->value[0] == delimiter)
			if (lst->prev && lst->prev->type == 'H')
				return (1);
	}
	return (0);
}

void	expand(char *prompt, t_lexer **lex)
{
	t_lexer	*lst;
	char	*tmp;

	lst = *lex;
	(void) prompt;
	while (lst)
	{
		if (lst->value[0] == '$' && lst->in_quotes != 2 && lst->value[1]
		&& !is_heredoc(lst))
		{
			lst->value++;
			lst->value = my_strdup(my_get_env(env, lst->value));
			if (lst->value[0] == '\"')
				rmv_d_qts(&lst->value);
			if (lst->value[0] == '\'')
				rmv_d_qts(&lst->value);
		}
		else if (lst->value[0] == '~' && !lst->in_quotes)
		{
			lst->value++;
			tmp = lst->value;
			lst->value = my_strdup(my_get_env(env, "HOME"));
			lst->value = my_strjoin(lst->value, tmp);
		}
		lst = lst->next;
	}
}
