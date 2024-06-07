/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 12:56:44 by smarsi            #+#    #+#             */
/*   Updated: 2024/06/03 16:31:22 by mchihab          ###   ########.fr       */
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
# define BUFFER_SIZE 1

int			ft_isdigit(int c);
int			ft_isalpha(int c);
size_t		ft_strlen(const char *s);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
long long	ft_atoi(char *str);
void		*ft_memset(void *b, int c, size_t len);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(int count, int size);
char		*ft_strdup(const char *s1);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_itoa(int n);
int			ft_isalnum(int c);
char		*get_next_line(int fd);
char		*ft_strjoin_ws(char const *s1, char const *s2);
char		*ft_strjoin_get(char *s1, char *s2);
char		*ft_sstrchr(char *str, int c);

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
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
#endif
