#include "../../minishell.h"

static char	*my_strjoin_c(char *s1, char s2)
{
	char	*str;
	int		len;

	if (!s1 && !s2)
		return (NULL);
	else if (!s2)
		return (s1);
	else if (!s1)
		len = 2;
	else
		len = (ft_strlen(s1) + 1) + 1;
	str = malloc(len * sizeof(char));
	if (!str)
		return (NULL);
	str[0] = '\0';
	if (s1)
		ft_strlcat(str, s1, ft_strlen(s1) + 1);
	str[len - 2] = s2;
	str[len - 1] = '\0';
	free(s1);
	return (str);
}


static char	*ft_strjoin_s(char  *s1, char  *s2)
{
	char	*p;
	int		i;
	int		j;
	size_t	lens1;
	size_t	lens2;

	if (!s1 || !s2)
		return (0);
	lens1 = ft_strlen((char *)s2);
	lens2 = ft_strlen((char *)s1);
	p = (char *)malloc(sizeof(char) * lens1 + lens2 + 1);
	if (!p)
		return (0);
	i = -1;
	while (s1[++i])
		p[i] = s1[i];
	j = -1;
	while (s2[++j])
		p[i++] = s2[j];
	p[i] = '\0';
	free(s1);
	return (p);
}

char	*heredoc_expand(char *line)
{
	char	(*tmp), (*new);
	int		(i) , (start);
	tmp = NULL;
	new = NULL;
	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			i++;
			start = i;
			while (line[i] && (ft_isalpha(line[i]) || ft_isdigit(line[i]) || line[i] == '_'))
				i++;
			tmp = ft_malloc((i - start) + 1, 0);
			if (!tmp)
			{
				free(line);
				return (NULL);
			}
			ft_strlcpy(tmp, line + start, (i - start) + 1);
			tmp = my_get_env(env, tmp);
			new = ft_strjoin_s(new, tmp);
			i--;
		}
		else
			new = my_strjoin_c(new, line[i]);
		i++;
	}
	free(line);
	return (new);
}