#include "minishell.h"

t_envp *env = NULL;

void	minishell()
{
	char	*prompt;
	t_lexer  *lex;

	lex = NULL;
	while (1)
	{
		// ft_lstclear(&lex);
		prompt = readline("minishell$ ");
		if (prompt[0] == '\0')
			return ;
		if (!prompt)
			return ;
		valid_prompt(prompt);
		lexer(prompt, &lex);
		printf("========= end lexer\n");
		while (lex)
		{
			printf("value is :%s, type is : %c, in_quotes : %d\n", \
			lex->value, lex->type, lex->in_quotes);
			lex = lex->next;
		}
		free(prompt);
	}
}

int	main(int ac, char *av[], char *envp[])
{
	if (ac > 1)
		ft_error("invalid number of params.\n", 126);
	(void)av;
	handle_env(&env, envp);
	minishell();
	// ft_export(&data,env);
	// print_env_list(env);
	ft_malloc(0, 1);
	ft_lstclear_env(&env);
	return (0);
}


