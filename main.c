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
	t_data data;
	char *p="export a+=das  s+='sss' a+=habibia s=1 s";
	char **arr = ft_split(p,' ');
	// printf("%s", arr[3]);
	data.cmd = arr[0];
	data.args = arr;

	// exit(0);
	handle_env(&env, envp);
	// minishell();
	handle_builts(&data);
    // env = sort_list(env , ascending);
	print_env_list(env,"ex");

	ft_malloc(0, 1);
	// exit(0); 
	ft_lstclear_env(&env);
	ft_freed(arr);
	return (0);
}


