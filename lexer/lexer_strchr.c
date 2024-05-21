#include "../minishell.h"

void	lexer_strchr(char *str, char *dlmtrs, int *ind, int f)
{
	int	i;

	i = *ind;
	while (str[i] && in_delimiters(str[i], dlmtrs) == f)
		i++;
	*ind = i;
}

void	lexer_strchr_d(char *str, char *dlmtrs, int *ind, int f)
{
	int	i;

	i = *ind;
	while (str[i] && ((in_delimiters(str[i], dlmtrs) == f) || ft_isalpha(str[i]) || ft_isdigit(str[i])))
		i++;
	*ind = i;
}