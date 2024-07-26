/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 19:35:06 by smarsi            #+#    #+#             */
/*   Updated: 2024/07/26 19:53:10 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static char	*ft_strjoin_s(char *s1, char *s2)
{
	char	*p;
	int		i;
	int		j;
	size_t	lens1;
	size_t	lens2;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (ft_strdup(s2));
	lens1 = ft_strlen((char *)s2);
	lens2 = ft_strlen((char *)s1);
	p = (char *)malloc(sizeof(char) * (lens1 + lens2 + 1));
	if (!p)
		return (0);
	i = -1;
	while (s1 && s1[++i])
		p[i] = s1[i];
	j = -1;
	while (s2 && s2[++j])
		p[i++] = s2[j];
	p[i] = '\0';
	free(s1);
	return (p);
}

void	handle_status(char *tmp, char *new, int *i)
{
	tmp = ft_itoa(env->exit_status);
	new = my_strjoin2(new, tmp);
	(free(tmp), (*i)++);
}

int	heredoc_expand_continue(char *line, char *tmp, char *new, int *index)
{
	int (i), (start);
	i = *index;
	start = i;
	if (line[i] == '?')
		handle_status(tmp, new, &i);
	else
	{
		while (line[i] && (ft_isalpha(line[i]) || ft_isdigit(line[i])
				|| line[i] == '_'))
			i++;
		tmp = ft_malloc((i - start) + 1, 0);
		if (!tmp)
		{
			free(line);
			return (1);
		}
		ft_strlcpy(tmp, line + start, (i - start) + 1);
		tmp = my_get_env(env, tmp);
		new = ft_strjoin_s(new, tmp);
	}
	*index = i;
	return (0);
}

char	*heredoc_expand(char *line)
{
	char	*tmp;
	char	*new;
	int		i;

	tmp = NULL;
	new = NULL;
	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] != '\n')
		{
			i++;
			if (heredoc_expand_continue(line, tmp, new, &i))
				return (NULL);
			i--;
		}
		else
			new = my_strjoin_c(new, line[i]);
		i++;
	}
	free(line);
	return (new);
}
