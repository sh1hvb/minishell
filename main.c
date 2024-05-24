#include "minishell.h"

t_data	*pars_lstnew(char *value, int quotes);
void	pars_lstclear(t_data **lst);

void	minishell()
{
	char	*prompt;
	t_lexer  *lex;
	t_data	*data;

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
		// while (lex_tmp)
		// {
		// 	printf("##########################\nvalue is :%s, type is : %c, in_quotes : %d\n", \
		// 	lex_tmp->value, lex_tmp->type, lex_tmp->in_quotes);
		// 	lex_tmp = lex_tmp->next;
		// }
		printf("========= end lexer\n");
		expand(prompt, &lex);
		// while (lex_tmp)
		// {
			// printf("##########################\nvalue is :%s, type is : %c, in_quotes : %d\n", \
			// lex_tmp->value, lex_tmp->type, lex_tmp->in_quotes);
			// lex_tmp = lex_tmp->next;
		// }
		(void) lex_tmp;
		printf("========= end expand\n");
		parsing(prompt, &lex, &data);
		printf("========= end parsing\n");
		while (data)
		{
			// int i = 0;
			printf("##########################\n value is :%s\n", data->cmd);
			// while (data->args[i])
			// {
			// 	printf(" args[%d] : \n", data->args[i]);
			// 	i++;
			// }
			printf("in_quotes : %d, in_file : %s, out_file : %s\n", \
			data->in_quotes, data->redir_in, data->redir_out);
			printf("##########################\n");
			data = data->next;
		}
		free(prompt);
	}
}
void print_env_list(t_envp *env_list)
{
    t_envp *current = env_list;
    while (current)
    {
        printf("%s=%s\n", current->key, current->value);
        current = current->next;
    }
}
int	main(int ac, char *av[], char *envp[])
{
	t_envp *env;
	env = NULL;

	(void) av;
	if (ac > 1)
		ft_error("invalid number of params.\n", 126);
	handle_env(&env, envp);
	minishell();
	// print_env_list(env);
	ft_malloc(0, 1);
	ft_lstclear_env(&env);
	return (0);
}


