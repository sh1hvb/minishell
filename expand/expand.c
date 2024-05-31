#include "../minishell.h"

void	rmv_s_qts(char **str)
{
	char	*tmp;
	int		i;

	i = 0;;
	(*str)++;
	tmp = *str;
	while(tmp[i])
	{
		if (tmp[i] == '\'')
		{
			tmp[i] = '\0';
			break;
		}
		i++;
	}
}

void	rmv_d_qts(char **str)
{
	char	*tmp;
	int		i;

	i = 0;;
	(*str)++;
	tmp = *str;
	while(tmp[i])
	{
		if (tmp[i] == '\"')
		{
			tmp[i] = '\0';
			break;
		}
		i++;
	}
}

void    expand(char *prompt, t_lexer **lex)
{
	t_lexer	*lst;
	char    *tmp;

	lst = *lex;
	(void) prompt;
    while (lst)
    {
		if (lst->value[0] == '$' && lst->in_quotes != 2 && lst->value[1])
		{
			lst->value++;
			lst->value = my_strdup(my_get_env(env, lst->value));
			if (lst->value[0] == '\"')
				rmv_d_qts(&lst->value);
			else if (lst->value[0] == '\'')
				rmv_d_qts(&lst->value);
		}
		else if (lst->value[0] == '~' && !lst->in_quotes)
		{
			lst->value++;
			tmp = lst->value;
			lst->value = my_strdup(my_get_env(env, "HOME"));
			lst->value = my_strjoin(lst->value, tmp);
		}
		// if (lst->value[0] == '\"' && lst->in_quotes != 2)
		// 	lst->prev->next = lst->next;
		// else if (lst->value[0] == '\'' && lst->in_quotes != 1)
		// 	rmv_s_qts(&lst->value);
		lst = lst->next;
    }
}