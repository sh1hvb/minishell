#include "../minishell.h"

void	*my_calloc(int count, int size)
{
	void	*ptr;

	ptr = ft_malloc(count * size, 0);
	if (!ptr)
		return (ptr);
	ft_bzero(ptr, count * size);
	return (ptr);
}

char	*my_strdup(char *s1)
{
	char	*s1_dup;
	int		len;

	if (!s1)
		return (my_strdup(""));
	len = ft_strlen(s1);
	s1_dup = my_calloc(len + 1, sizeof(char));
	if (!s1_dup)
		return (NULL);
	ft_strlcpy(s1_dup, s1, len + 1);
	return (s1_dup);
}

char	*my_strjoin(char *s1, char *s2)
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
	return (str);
}

char	*my_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*p;

	if (!s)
		return (0);
	i = 0;
	if (start >= ft_strlen(s))
		return (my_strdup(""));
	else if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	p = (char *)ft_malloc((len + 1) * sizeof(char), 0);
	if (!p)
		return (0);
	while (i < len && s[i] && start <= ft_strlen(s))
	{
		p[i] = s[start];
		if (!p[i])
			return (0);
		start++;
		i++;
	}
	p[i] = '\0';
	return (p);
}
