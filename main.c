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

void	minishell(char *envp[])
{
	char	*prompt;
	t_lexer  *lex;
	t_data *data;
	int status;
	while (1)
	{
		// ft_lstclear(&lex);
		// pars_lstclear(&data);
		lex = NULL;
		data = pars_lstnew(NULL, 0);
		prompt = readline("minishell$ ");
		if (!prompt)
			return ;
		add_history(prompt);
		status = valid_quotes(prompt);
		if (status)
		{
			free(prompt);
			continue;
		}
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
			parsing(&lex, &data);
			// print_parsing(pars_tmp);
			// printf("\n\n");
			// printf("========= end pars\n");
			(void) envp;
			process_cmd(data);
			// handle_builts(data);
			// printf("========= end parsing\n");
		}
 		ft_malloc(0, 1);
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

	handle_env(envp);
	// char **test =NULL;
	// test = list_to_pointer();
	// int i = 0;
	// while(test[i])
	// {
	// 	printf("%s\n", test[i]);
	// 	i++;
	// }
	// exit(0);
	minishell(envp);
    // env = sort_list(env , ascending);
	// print_env_list(env,"en");
	ft_malloc(0, 1);
	// exit(0); 
	ft_lstclear_env(&env);
	// ft_freed(arr);
	return (0);
}


