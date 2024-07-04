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
		while (lst && lst->value[0] != delimiter)
			lst = lst->prev;
		if (lst && lst->value[0] == delimiter)
			if (lst->prev && lst->prev->type == 'H')
				return (1);
	}
	return (0);
}

char	*my_strjoin2(char *s1, char *s2)
{
	char	*str;
	int		len;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (my_strdup(s2));
	else if (!s2)
		return (my_strdup(s1));
	len = (ft_strlen(s1) + ft_strlen(s2)) + 1;
	str = ft_malloc(len * sizeof(char), 0);
	if (!str)
		return (str);
	str[0] = '\0';
	ft_strlcat(str, s1, ft_strlen(s1) + 1);
	ft_strlcat(str, s2, len);
	free(s1);
	return (str);
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
			if (lst->value[0] == '?')
				lst->value = my_strjoin2(ft_itoa(env->exit_status), lst->value + 1);
			else
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
