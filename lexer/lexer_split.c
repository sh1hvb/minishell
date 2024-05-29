#include "../minishell.h"

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
            skip_quotes(s, '\"', &i);
			while (s[i] && !in_delimiters(s[i], " \t\n\"\'"))
				i++;
			if (flag)
            	count++;
        }
        else if (s[i] == '\'') {
            skip_quotes(s, '\'', &i);
			while (s[i] && !in_delimiters(s[i], " \t\n\"\'"))
				i++;
            if (flag)
            	count++;
        }
		if (!in_delimiters(s[i], delimiters) && flag && s[i])
		{
			count++;
			flag = 0;
		}
		if (in_delimiters(s[i], delimiters))
			flag = 1;
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
        skip_quotes(src, '\"', &i); 
		while (src[i] && !in_delimiters(src[i], " \t\n\"\'"))
			i++;
	}
    else if (src[i] == '\'')
	{
        skip_quotes(src, '\'', &i);
		while (src[i] && !in_delimiters(src[i], " \t\n\"\'"))
			i++;
	}
    else
	    while (src[i] && !in_delimiters(src[i], delimiters))
		{
		    i++;
			if (src[i] == '\"')
			{
        		skip_quotes(src, '\"', &i); 
				while (src[i] && !in_delimiters(src[i], " \t\n\"\'"))
					i++;
			}
    		else if (src[i] == '\'')  
			{
        		skip_quotes(src, '\'', &i);	
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
	count = count_word(s, delimiters);
	dst = my_calloc(count + 1, sizeof(char *));
	if (!dst)
		return (NULL);
	dst = fill_array(dst, s, delimiters, count);
	return (dst);
}

// int main(int ac, char *av[])
// {
//     char **spliter = lexer_split(av[1], av[2]);
//     int i = 0;
//     while (spliter[i])
//     {
//         printf("%s\n", spliter[i]);
//         i++;
//     }
//     return 0;
// gcc lexer/lexer_split.c lexer/lexer_helper.c libft_ftmalloc/free_libft.c libft/libft.a memory_handling/*.c
// }