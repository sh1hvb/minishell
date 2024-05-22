#include "minishell.h"

t_data  *data;

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
		expand(prompt, &lex);
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


