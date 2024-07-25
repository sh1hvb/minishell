#include "../minishell.h"

char	**fill_array(char **dst, char *src, char *delimiters, int num_word);

static void	handle_quotes(char *s, int *index, int *count, int flag)
{
	int	i;

	i = *index;
	if (s[i] == '\"')
	{
		split_quotes(s, '\"', &i);
		while (s[i] && !in_delimiters(s[i], " \t\n"))
			i++;
		if (flag)
			(*count)++;
	}
	else if (s[i] == '\'')
	{
		split_quotes(s, '\'', &i);
		while (s[i] && !in_delimiters(s[i], " \t\n"))
			i++;
		if (flag)
			(*count)++;
	}
	*index = i;
}

static int	count_word(char *s, char *delimiters)
{
	int	count;
	int	flag;
	int	i;

	count = 0;
	flag = 1;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\"' || s[i] == '\'')
			handle_quotes(s, &i, &count, flag);
		if (s[i] && !in_delimiters(s[i], delimiters) && flag)
		{
			count++;
			flag = 0;
		}
		if (s[i] && in_delimiters(s[i], delimiters))
			flag = 1;
		if (!s[i])
			break ;
		i++;
	}
	return (count);
}

char	**lexer_split(char *s, char *delimiters)
{
	char	**dst;
	int		count;

	if (!s || !delimiters)
	{
		return (NULL);
	}
	count = 0;
	count = count_word(s, delimiters);
	dst = my_calloc(count + 1, sizeof(char *));
	if (!dst)
		return (NULL);
	dst = fill_array(dst, s, delimiters, count);
	return (dst);
}
