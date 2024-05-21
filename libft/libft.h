/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 12:56:44 by smarsi            #+#    #+#             */
/*   Updated: 2024/05/21 14:40:01 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdio.h>
# include <ctype.h>
# include <string.h>
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>
# include "../minishell.h" 

int			ft_isdigit(int c);
int			ft_isalpha(int c);
size_t		ft_strlen(const char *s);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
long long	ft_atoi(char *str);
void		*ft_memset(void *b, int c, size_t len);
void		ft_bzero(void *s, size_t n);
void	*ft_calloc(int count, int size);
char		*ft_strdup(const char *s1);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
char		*ft_substr(char const *s, unsigned int start, size_t len);

typedef struct s_lexer t_lexer;
typedef struct s_list
{
	int				content;
	int				index;
	struct s_list	*next;
}	t_stack;
t_lexer		*ft_lstnew(char *value, int type, int quotes);
void		ft_lstadd_front(t_lexer **lst, t_lexer *new);
void		*ft_malloc(int size, int flag);

int			ft_lstsize(t_lexer *lst);
t_lexer		*ft_lstlast(t_lexer *lst);
void		ft_lstadd_back(t_lexer **lst, t_lexer *new);
void		ft_lstdelone(t_lexer *lst);
void		ft_lstclear(t_lexer **lst);
void		ft_lstiter(t_lexer **lst);
void		lexer_strchr(char *str, char *dlmtrs, int *ind, int f);

#endif
