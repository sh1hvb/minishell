
#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

typedef struct s_envp
{
	char			*key;
	char			*value;
	int				flag;
	int				signal_heredoc;
	int				exit_status;
	struct s_envp	*next;
	struct s_envp	*prev;
}					t_envp;

extern t_envp		*env;

enum				token
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
}					t_lexer;

typedef struct t_files
{
	char			*buffer;
	char			*delimiter;
	int				index;
	int				type;
	struct t_files	*next;
	struct t_files	*prev;
}					t_files;

typedef struct s_data
{
	char			*cmd;
	char			**args;
	int				in_quotes;
	int				has_heredoc;
	t_files			*redir_out;
	t_files			*redir_in;
	t_files			*append;
	t_files			*heredoc;
	int				infile;
	int				outfile;
	int				appfile;
	struct s_data	*next;
	struct s_data	*prev;

}					t_data;
typedef struct s_leaks
{
	void			*add;
	struct s_leaks	*next;
}					t_leaks;

// made by mchihab
/*===============================* EXCUTION *===================================================*/
/* CMDS */
// check_cmd
void				check_redir(t_data *data, t_files *file);
void				hide_inout(int a);
void				check_empty_cmd_two(t_data *data);
void				process_cmd(t_data *data);
//error cmd
void				handle_execve_error(char *cmd);
void				handle_access_error(char *cmd);
//execute
bool				is_directory(char *path);
void				handle_child_execution(t_data *data);
void				exec(t_data *data);
void				handle_process_execution(t_data *data);
void				process_pipe(t_data *data);
//piping
void				ft_execute_multiple(t_data *data);
void				create_pipes(t_data *data);
//single cmd
void				handle_redirections(t_data *data);
void				handle_execve(t_data *data, char *path, char **envp);
void				execute_built_in_or_fork(t_data *data);
void				execute_single_cmd(t_data *data);
// utils_exec
void				handle_directory_error(char *cmd);
char				*check_access_cmd(char **allpath, char *cmd, int i);
char				*get_path(char *cmd);
//utils single
int					handle_file_redirections(t_data *data);
void				setup_redirections(t_data *data);
void				close_file_descriptors(t_data *data);
/* END CMDS */

/* REDIRECTIONS */
// herdoc
int					end_heredoc(char *line, char *delimiter);
void				heredoc_read_and_put_mult(t_data *data, int fdp);
void				heredoc_mult(t_data *data);
//here doc expand
char				*heredoc_expand(char *line);
// linked list file
int					ft_lstsize_file(t_files *lst);
t_files				*ft_lstlast_file(t_files *lst);
//redirection
int					ft_input(t_files *file);
int					ft_output(t_files *file);
int					ft_append_file(t_files *file);
void				handle_child_redirections(t_data *data, int fds[]);
void				handle_heredoc(t_data *data);
//utils heredoc
int					check_heredoc_two(t_data *data);
int					check_heredoc(t_data *data);
void				err(void);
void				call_here_put(t_data *p, int fds);
//utils redirection
void				handle_process_redirections(t_data *data);
void				handle_append_redirection(t_data *data);
void				handle_output_redirection(t_data *data);
void				handle_input_redirection(t_data *data);
/* END REDIRECTIONS */

/* UTILS BUILTINS */
//mini utils export
int					ascending(int a, int b);
int					if_flag(char *s);
int					check_equal(char *s);
void				handle_no_arguments(t_envp *env);
int					handle_no_first_element(char **arr);
//utils export
t_envp				*sort_list(t_envp *lst, int (*cmp)(int, int));
t_envp				*my_append_env(t_envp *env_list, const char *key,
						char *value);
void				ft_append(t_data *data, t_envp *env, int i);
/* END UTILS BUILTINS */

//builtins checker
int					check_builts(t_data *data);
void				handle_builts(t_data *data);
//builtins split
char                **fill_array_b(char **dst, char *src, char *delimiters, int num_word);

char				**builtins_split(char *s, char *delimiters);
// cd
void				ft_cd(t_data *data);
void				cd_old_pwd(t_data *data, char *msg);
void				cd_home(t_data *data, char *msg);
void				set_pwd(char *cwd);
void				get_old_pwd(void);
// echo
void				echo_without_flag(t_data *parce);
void				echo_print(t_data *parce, int i);
void				ft_echo(t_data *parce);
// exit
int					is_number(char *arg);
long long			ft_atoi2(char *str);
void				ft_exit(t_data *data);
// export
void				ft_export(t_data *data, t_envp *env);
void				process_arguments(t_data *data, t_envp *env, int i);
void				handle_flag_set(t_data *data, t_envp *env, int i,
						char **arr);
char				*my_get_env(t_envp *env_list, const char *key);
void				ft_env(void);
// pwd
void				ft_pwd(t_data *data);
// unset;
void				ft_unset(t_data *data);
void				remove_node(t_envp *head, t_data *data, int i);
void				condition(t_envp *head);
// linked list env
int					ft_lstsize_env(t_envp *lst);
void				ft_lstadd_front_env(t_envp **lst, t_envp *new);
t_envp				*ft_lstlast_env(t_envp *lst);
void				ft_lstdelone_env(t_envp *lst);
t_envp				*ft_lstnew_env(char *value, t_envp *env, int flag);
// env
t_envp				*get_env(char **env, int c);
void				ft_lstclear_env(t_envp *lst);
void				handle_env(char *envp[]);
void				new_env(void);
void				print_env_list(char *x);
// utils env
int					check_string(char *s);
void				inc_shell(void);
char				**list_to_pointer(void);
void				ft_lstadd_back_env(t_envp **lst, t_envp *new);

// init env
t_envp				*build_env_list(char **env, int c);
/*===============================* END EXCUTION *===================================================*/

// made by smarsi
void				*ft_malloc(int size, int flag);
t_leaks				*free_lstlast(t_leaks *lst);
int					ft_error(char *msg, int ext);
void				lexer(char *prompt, t_lexer **lex);
void				skip_delimiters(char *str, char *delimiters, int *index);
int					in_delimiters(char target, char *delimiters);
void				get_cmds(char *prompt, t_data **data, int *index);
void				get_quotes(char *prompt, t_data **data, int *index);
void				skip_quotes(char *target, char delimiter, int *index);
t_envp				*get_env(char **env, int c);
void				ft_freed(char **p);
char				**lexer_split(char *s, char *delimiters);
void				lexer_strchr_d(char *str, char *dlmtrs, int *ind, int f);
void				is_dollar(char *prompt, t_lexer **lex, int *index,
						int flag);
void				expand(char *prompt, t_lexer **lex);
int					parsing(t_lexer **lex, t_data **data);
char				*my_strdup(char *s1);
void				*my_calloc(int count, int size);
char				*my_strjoin(char *s1, char *s2);
char				*my_substr(char const *s, unsigned int start, size_t len);
int					pipe_syntax(t_lexer *lex);
int					check_syntax(t_lexer *lex);
int					valid_quotes(char *prompt);
int					files_syntax(t_lexer *lex);
void				helpers_lines(t_data **data, t_files ***head, int flag,
						char *name);
void				initialize_cmd(t_data *data_tmp);
void				remove_quotes(t_data *data_tmp);
void				process_cmd(t_data *data);
int					ft_append_file(t_files *file);
void				sigint_handler(int sig);
void				sigint_int(int sig);
void				signal_quit(int sig);
void				sig_quit_heredoc(int sig);
void				sigint_heredoc(int sig);
char				*my_strjoin2(char *s1, char *s2);
int					is_heredoc(t_lexer *lst);
int					heredoc_lstsize(t_files *lst);
t_data				*pars_lstnew(char *value, int quotes);
void				pars_lstadd_back(t_data **lst, t_data *new);
void				heredoc_lstadd_back(t_files **lst, t_files *new);
t_files				*heredoc_lstnew(char *value);
t_files				*heredoc_lstlast(t_files *lst);
int					is_valid_type(t_lexer *lex);
int					is_ambiguous(t_lexer *lex);
int					pars_files(t_data **data, t_lexer **lex, int flag);
void				fill_args(t_lexer **lex, t_data **data, int export_flag);
void				new_node(t_lexer **lex, t_data **data);
void				split_quotes(char *target, char delimiter, int *index);
void				heredoc_counter(t_lexer *lex);
void				cd_old_pwd_continue(char *tmp);
int					ft_cd_continue(t_data *data);
#endif
