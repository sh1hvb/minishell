#include "minishell.h"

t_envp *env = NULL;
int a = 0;
int	pars_lstsize(t_data *lst);

t_data	*pars_lstnew(char *value, int quotes);
void	pars_lstclear(t_data **lst);
void	heredoc_lstadd_back(t_files **lst, t_files *new);
t_files	*heredoc_lstnew(char *value);
void    print_expand(t_lexer *lex_tmp);
void    print_parsing(t_data *data);
void    print_lexer(t_lexer *lex_tmp);

void	minishell()
{
	char	*prompt;
	t_lexer  *lex;
	t_data *data;
	int status = 0;

	while (1)
	{
		// ft_lstclear(&lex);
		// pars_lstclear(&data);
		(signal(SIGINT, sigint_handler), signal(SIGQUIT, SIG_IGN));
		prompt = NULL;
		lex = NULL;
		data = pars_lstnew(NULL, 0);
		prompt = readline("minishell$ ");
		(signal(SIGINT, sigint_int), signal(SIGQUIT, signal_quit));
		if (!prompt)
		{
			printf("exit\n");
			return ;
		}
		else if (!prompt[0])
		{
			free(prompt);
			continue ;
		}
		if (prompt && ft_strcmp(prompt, ""))
			add_history(prompt);
		status = valid_quotes(prompt);
		if (status)
		{
			free(prompt);
			continue;
		}
		lexer(prompt, &lex);
		// t_lexer *lex_tmp = lex;
		// print_lexer(lex_tmp);
		// printf("========= end lexer\n");
		status = check_syntax(lex);
		if (!status)
		{
			expand(prompt, &lex);
			// print_expand(lex_tmp);
			// printf("========= end expand\n");
			heredoc_counter(lex);
			if (parsing(&lex, &data))
			{
				free(prompt);
				continue;
			}
			// print_parsing(data);
			// printf("\n\n");
			// printf("========= end pars\n");
			process_cmd(data);
			// handle_builts(data);
			// printf("========= end parsing\n");
		}
		// handle_builts(data);
		// printf("========= end parsing\n");
		free(prompt);
		ft_malloc(0, 1);
	}
}

int	main(int ac, char *av[], char *envp[])
{
	int	exit_status;

	exit_status = 0;
	if (ac > 1)
		ft_error("invalid number of params.\n", 126);
	(void)av;

	handle_env(envp);
	inc_shell();
	minishell();
	ft_lstclear_env(env);
    // env = sort_list(env , ascending);
	// print_env_list(env,"en");
	ft_malloc(0, 1);
	// exit(0); 
	// ft_freed(arr);
	return (exit_status);
}
