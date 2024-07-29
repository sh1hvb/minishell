/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 20:17:11 by mchihab           #+#    #+#             */
/*   Updated: 2024/07/29 20:11:02 by mchihab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
 int in_delimiterss(char c, char *delimiters) 
 {
    while (*delimiters)
	{
        if (c == *delimiters)
            return 1;
        delimiters++;
    }
    return 0;
}
char *find_first_delimiter(const char *s, char *delimiters) 
{
    int i;

	i = 0;
    while (s[i])
	{
        if (in_delimiterss(s[i], delimiters)) 
            return (char *)&s[i];
        i++;
    }
    return NULL;
}

char **create_result_array(char *first_part, char *second_part, int has_delimiter) 
{
    char **result;

    result = malloc((has_delimiter ? 3 : 2) * sizeof(char *));
    if (!result) 
	{
        free(first_part);
        free(second_part);
        return NULL;
    }
    result[0] = first_part;
    result[1] = second_part;
    if (has_delimiter) 
        result[2] = NULL;
	else 
        result[1] = NULL;

    return result;
}

char **split_with_first_delimiter(char *s, char *delimiters) {
    char **result;
    char *first_part;
    char *second_part;
    char *delim_position;

    if (!s || !delimiters)
        return NULL;
    delim_position = find_first_delimiter(s, delimiters);
    if (!delim_position)
        return create_result_array(ft_strdup(s), NULL, 0);
    first_part = ft_strndup(s, delim_position - s);
    second_part = ft_strdup(delim_position + 1);
    result = create_result_array(first_part, second_part, 1);
    return result;
}
