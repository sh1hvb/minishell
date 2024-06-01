#include "../minishell.h"

void	split_quotes(char *target, char delimiter, int *index);

static	void	ft_free(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}

static	int	count_word(char  *s, char *delimiters)
{
	int	count;
	int	flag;
	int	i;

	count = 0;
	flag = 1;
	i = 0;
	while (s[i])
	{
        if (s[i] == '\"')
        {
            split_quotes(s, '\"', &i);
			while (s[i] && !in_delimiters(s[i], " \t\n\"\'"))
				i++;
			if (flag)
            	count++;
        }
        else if (s[i] && s[i] == '\'') {
            split_quotes(s, '\'', &i);
			while (s[i] && !in_delimiters(s[i], " \t\n\"\'"))
				i++;
            if (flag)
            	count++;
        }
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

static	char	*get_word(char *dst, char  *src, char *delimiters, int	*index)
{
	int	i;
	int	start;
	int	len;

	i = *index;
	while (src[i] && in_delimiters(src[i], delimiters))
		i++;
	start = i;
    if (src[i] == '\"')
	{
        split_quotes(src, '\"', &i); 
		while (src[i] && !in_delimiters(src[i], " \t\n\"\'"))
			i++;
	}
    else if (src[i] == '\'')
	{
        split_quotes(src, '\'', &i);
		while (src[i] && !in_delimiters(src[i], " \t\n\"\'"))
			i++;
	}
    else
	    while (src[i] && !in_delimiters(src[i], delimiters))
		{
		    i++;
			if (src[i] == '\"')
			{
        		split_quotes(src, '\"', &i); 
				while (src[i] && !in_delimiters(src[i], " \t\n\"\'"))
					i++;
			}
    		else if (src[i] == '\'')  
			{
        		split_quotes(src, '\'', &i);	
				while (src[i] && !in_delimiters(src[i], " \t\n\"\'"))
					i++;
			}
		}
	len = (i - start) + 1;
	dst = my_calloc(len, sizeof(char));
	ft_strlcpy(dst, src + start, len);
	*index = i;
	return (dst);
}

static char	**fill_array(char **dst, char *src, char *delimiters, int number_word)
{
	int	i;
	int	index_word;

	index_word = 0;
	i = 0;
	while (i < number_word)
	{
		dst[i] = get_word(dst[i], src, delimiters, &index_word);
		if (!dst[i])
			ft_free(dst);
		i++;
	}
	return (dst);
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
