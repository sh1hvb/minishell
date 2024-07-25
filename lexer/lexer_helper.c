#include "../minishell.h"

int	in_delimiters(char target, char *delimiters);

void	skip_quotes(char *target, char delimiter, int *index)
{
	int	i;

	i = *index;
	i++;
	while (target[i] && target[i] != delimiter)
		i++;
	if (target[i] == delimiter)
		i++;
	*index = i;
}

void	split_quotes(char *target, char delimiter, int *index)
{
	int	i;

	i = *index;
	i++;
	while (target[i])
	{
		if (target[i] == delimiter)
		{
			i++;
			if (target[i] == '\'' || target[i] == '\"')
				delimiter = target[i];
			else
				break ;
		}
		i++;
	}
	*index = i;
}

void	get_cmds(char *prompt, t_data **data, int *index)
{
	int	i;

	(void)data;
	i = *index;
	if (prompt[i] && in_delimiters(prompt[i], " \t\n\v\v\f\r"))
	{
		printf("%c", prompt[i]);
		i++;
	}
	while (prompt[i] && !in_delimiters(prompt[i], " \t\n\v\v\f\r"))
	{
		printf("%c", prompt[i]);
		i++;
	}
	*index = i;
}

void	get_quotes(char *prompt, t_data **data, int *index)
{
	char	c;
	int		i;

	(void)data;
	i = *index;
	c = prompt[i];
	printf("%c", c);
	i++;
	while (prompt[i] && c != prompt[i])
	{
		printf("%c", prompt[i]);
		i++;
	}
	if (c == prompt[i])
		printf("%c", prompt[i++]);
	printf("\n");
	*index = i;
}

int	in_quotes(char prompt, int *flag_sq, int *flag_dq)
{
	if (prompt == '\"' && !*flag_sq)
	{
		if (*flag_dq == 0)
			*flag_dq = 1;
		else
			*flag_dq = 0;
	}
	else if (prompt == '\'' && !*flag_dq)
	{
		if (*flag_sq)
			*flag_sq = 0;
		else
			*flag_sq = 1;
	}
	if (*flag_sq)
		return (2);
	if (*flag_dq)
		return (1);
	return (0);
}
