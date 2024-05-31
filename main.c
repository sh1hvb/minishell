#include "minishell.h"

int	pars_lstsize(t_data *lst);

t_envp *env = NULL;

t_data	*pars_lstnew(char *value, int quotes);
void	pars_lstclear(t_data **lst);
void	heredoc_lstadd_back(t_files **lst, t_files *new);
t_files	*heredoc_lstnew(char *value);
void    print_expand(t_lexer *lex_tmp);
void    print_parsing(t_data *data);
void    print_lexer(t_lexer *lex_tmp);

void	minishell(char *envp[])
{
	char	*prompt;
	t_lexer  *lex;
	t_data *data;

	while (1)
	{
		// ft_lstclear(&lex);
		// pars_lstclear(&data);
		lex = NULL;
		data = pars_lstnew(NULL, 0);
		prompt = readline("minishell$ ");
		if (prompt[0] == '\0')
			return ;
		if (!prompt)
			return ;
		valid_prompt(prompt);
		lexer(prompt, &lex);
		t_lexer  *lex_tmp = lex;
		(void) lex_tmp;
		// print_lexer(lex_tmp);
		// printf("========= end lexer\n");
		expand(prompt, &lex);
		// print_expand(lex_tmp);
		// printf("========= end expand\n");
		parsing(prompt, &lex, &data);
		// print_parsing(data);
		check_cmd(data , env, envp);
		// handle_builts(data);

		// printf("========= end parsing\n");
		free(prompt);
	}
}

int	main(int ac, char *av[], char *envp[])
{
	if (ac > 1)
		ft_error("invalid number of params.\n", 126);
	(void)av;

	// exit(0);
	handle_env(&env, envp);
	minishell(envp);
    // env = sort_list(env , ascending);
	// print_env_list(env,"en");

	ft_malloc(0, 1);
	// exit(0); 
	ft_lstclear_env(&env);
	// ft_freed(arr);
	return (0);
}


