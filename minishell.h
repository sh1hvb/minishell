
#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"
# include <sys/wait.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <signal.h>
#include <termios.h>
#include <stdbool.h>

// typedef struct s_data
// {
// 	char			**args;
// 	struct s_data	*data;
// 	struct s_data	*next;
// }	t_data;
typedef struct s_envp
{
	char *key;
	char *value;
	int flag;
	int signal_heredoc;
    int exit_status;
	struct s_envp *next;
	struct s_envp *prev;
} t_envp;

extern t_envp *env;
extern int a;
enum token
{
	STRING = 'S',
	IN_FILE = 'I',
	OUT_FILE = 'O',
	PIPE = 'P',
	D_QUOTES = '\"',
	S_QUOTES = '\'',
	HEREDOC = 'H',
	IN_A_FILE = 'A',
	WITH_SPACE = 'W',
	DOLLAR = '$',
	UNSET = 'U',
};

typedef struct s_lexer
{
	char			*value;
	enum token		type;
	int				in_quotes;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

typedef struct t_files
{
	char			*buffer;
	char			*delimiter;
	int				index;
	int				type;
	struct t_files	*next;
	struct t_files	*prev;
}	t_files;

typedef struct s_data
{
	char			*cmd ;
	char			**args;
	int				in_quotes;
	int				has_heredoc;
	t_files			*redir_out;
	t_files			*redir_in;
	t_files			*append;
	t_files			*heredoc;
	int 			infile;
	int				outfile;
	int				appfile;
	struct s_data	*next;
	struct s_data	*prev;
	
}	t_data;
typedef struct s_leaks
{
    void *add;
    struct s_leaks *next;
}t_leaks;
// made by mchihab
// made by mchihab
void	ft_lstclear_env(t_envp **lst);
t_envp	*sort_list(t_envp *lst, int (*cmp)(int, int));
void	print_env_list(char *x);
void	ft_export(t_data *data , t_envp *env);
int		ft_lstsize_env(t_envp *lst);
void	ft_lstadd_back_env(t_envp **lst, t_envp *new);
t_envp	*ft_lstlast_env(t_envp *lst);
t_envp	*ft_lstnew_env(char *value, t_envp *env, int flag);
int		check_string(char *s);
void	handle_builts(t_data *data);
void	handle_env(char *envp[]);
int		ascending(int a, int b);
void	ft_env();
int		check_equal(char *s);
void	ft_pwd(t_data *data);
void	ft_lstdelone_env(t_envp *lst);
void	ft_unset(t_data *data);
void	ft_echo(t_data *data, t_envp *env);
void	ft_lstclear_env(t_envp **lst);
void 	ft_freed(char **p);
char	**builtins_split(char *s, char *delimiters);
char 	*my_get_env(t_envp *env_list, const char *key);
t_envp	*my_append_env(t_envp *env_list, const char *key, char *value);
void	ft_cd(t_data *data);
void    ft_exit(t_data *data);
int		check_builts(t_data *data );
void	check_cmd(t_data *data, t_envp *env, char *envp[]);
void	inc_shell();
char	**list_to_pointer();
void	dec_shell();
void 	execute_single_cmd(t_data *data);
void 	execute(t_data *data);
t_files	*ft_lstlast_file(t_files *lst);
void 	process_pipe(t_data *data);
void 	ft_execute_multiple(t_data *data);
void 	exec(t_data *data);
void 	create_pipes(t_data *data);
int		ft_output(t_files *file);
int		ft_input(t_files *file);
void	heredoc(t_data *data);
void 	heredoc_read_and_put(t_data *data, int *fdp);
int		ft_heredoc(t_files *file);
void heredoc_mult(t_data *data);
char    *heredoc_expand(char *line);
int 	check_heredoc(t_data * data);
 int	ft_lstsize_file(t_files *lst);
int check_sp(char *s);
char	*get_path(char *cmd);
int check_heredoc_two(t_data * data);
void handle_execve(t_data *data, char *path, char **envp);
void handle_directory_error(char *cmd);
void check_shlvl(t_data *data);
/**************************************************************************************************/
// made by smarsi 
void	*ft_malloc(int size, int flag);
t_leaks	*free_lstlast(t_leaks *lst);
int		ft_error(char *msg, int ext);
void	lexer(char *prompt, t_lexer **lex);
void	skip_delimiters(char *str, char *delimiters, int *index);
int		in_delimiters(char target, char *delimiters);
void	get_cmds(char *prompt, t_data **data, int *index);
void	get_quotes(char *prompt, t_data **data, int *index);
void	skip_quotes(char *target, char delimiter, int *index);
t_envp 	*get_env(char **env);
void 	ft_freed(char **p);
char	**lexer_split(char *s, char *delimiters);
void	lexer_strchr_d(char *str, char *dlmtrs, int *ind, int f);
void	is_dollar(char *prompt, t_lexer **lex, int *index, int flag);
void    expand(char *prompt, t_lexer **lex);
int		parsing(t_lexer **lex, t_data	**data);
char	*my_strdup( char *s1);
void	*my_calloc(int count, int size);
char	*my_strjoin(char *s1, char *s2);
char	*my_substr(char const *s, unsigned int start, size_t len);
int		pipe_syntax(t_lexer *lex);
int		check_syntax(t_lexer *lex);
int		valid_quotes(char *prompt);
int		files_syntax(t_lexer *lex);
void	helpers_lines(t_data **data, t_files ***head, int flag, char *name);
void	initialize_cmd(t_data *data_tmp);
void	remove_quotes(t_data *data_tmp);
void 	process_cmd(t_data *data);
int		ft_append_file(t_files *file);
void	sigint_handler(int sig);
void	sigint_int(int sig);
void	signal_quit(int sig);
void	sig_quit_heredoc(int sig);
void	sigint_heredoc(int sig);
char	*my_strjoin2(char *s1, char *s2);
#endif
