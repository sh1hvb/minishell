#include "../../minishell.h"

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
	str = malloc(len * sizeof(char));
	if (!str)
		return (str);
	str[0] = '\0';
	if (s1)
		ft_strlcat(str, s1, ft_strlen(s1) + 1);
	str[len - 2] = s2;
	str[len - 1] = '\0';
	free(s1);
	return (str);
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
			new = my_strjoin(new, tmp);
			i--;
		}
		else
			new = my_strjoin_c(new, line[i]);
		i++;
	}
	if (line)
		free(line);
	return (ft_strdup(new));
}