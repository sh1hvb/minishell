/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:58:44 by smarsi            #+#    #+#             */
/*   Updated: 2024/05/20 14:23:31 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"

// typedef struct s_data
// {
// 	char			**args;
// 	struct s_data	*data;
// 	struct s_data	*next;
// }	t_data;

// tokenization :

enum token
{
	STRING = 'S',
	IN_FILE = 'I',
	OUT_FILE = 'O',
	PIPE = 'P',
	D_QUOTES = 'D',
	S_QUOTES = 'Q',
	HEREDOC = 'H',
	IN_A_FILE = 'A',
	WITH_SPACE = 'W',
};

typedef struct s_lexer
{
	char			*value;
	enum token		type;
	int				in_quotes;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

typedef struct s_data
{
	char			*cmd;
	char			**args;
	char			redir_in;
	char			redir_out;
	int				in_quotes;
	struct s_data	*next;
	struct s_data	*prev;
	
}	t_data;
typedef struct s_leaks
{
    void *add;
    struct s_leaks *next;
}t_leaks;
t_leaks	*free_lstlast(t_leaks *lst);
void *ft_malloc(int size, int flag);
void	ft_error(char *msg, int ext);
void	valid_prompt(char *prompt);
void	lexer(char *prompt, t_lexer **lex);
void	skip_delimiters(char *str, char *delimiters, int *index);
int		in_delimiters(char target, char *delimiters);
void	get_cmds(char *prompt, t_data **data, int *index);
void	get_quotes(char *prompt, t_data **data, int *index);
void	skip_quotes(char *target, char delimiter, int *index);
char	**lexer_split(char *s, char *delimiters);
#endif