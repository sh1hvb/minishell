/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 18:22:40 by mchihab           #+#    #+#             */
/*   Updated: 2024/08/05 12:16:30 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp	*g_env = NULL;

int	readline_signals(t_lexer **lex, char **prompt)
{
	int	ex;

	*prompt = NULL;
	*lex = NULL;
	(signal(SIGINT, sigint_handler), signal(SIGQUIT, SIG_IGN));
	*prompt = readline("minishell$ ");
	(signal(SIGINT, sigint_int), signal(SIGQUIT, signal_quit));
	if (!*prompt)
	{
		printf("exit\n");
		ft_malloc(0, 1);
		ex = g_env->exit_status;
		ft_lstclear_env(g_env);
		exit (ex);
	}
	if (!*prompt[0])
	{
		free(*prompt);
		return (1);
	}
	if (*prompt && ft_strcmp(*prompt, ""))
		add_history(*prompt);
	return (0);
}

int	minishell_helper(char **prompt, t_lexer **lex, t_data **data)
{
	expand(*prompt, lex);
// ########### Uncomment the following lines if you want to check the expanded data : ##############
		// t_lexer *lex_tmp = *lex;
		// print_expand(lex_tmp);
		// printf("========= end expand\n");
// ##########################################################################
	heredoc_counter(*lex);
	if (parsing(lex, data))
	{
		free(*prompt);
		return (1);
	}
// ########## Uncomment the following lines if you need to check the data parsing : ########
		// print_parsing(*data);
		// printf("========= end pars\n");
// ##########################################################################
	process_cmd(*data);
	return (0);
}

void	minishell(void)
{
	char	*prompt;
	t_lexer	*lex;
	t_data	*data;

	while (1)
	{
		data = pars_lstnew(NULL, 0);
		if (readline_signals(&lex, &prompt))
			continue ;
		if (valid_quotes(prompt))
		{
			free(prompt);
			continue ;
		}
		lexer(prompt, &lex);
// ########## Uncomment the following lines if you need to check the lexer data : ########
		// t_lexer *lex_tmp = lex;
		// print_lexer(lex_tmp);
		// printf("========= end lexer\n");
// ##########################################################################

		if (!check_syntax(lex))
		{
			if (minishell_helper(&prompt, &lex, &data))
				continue ;
		}
		ft_malloc(0, 1);
		free(prompt);
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
	ft_lstclear_env(g_env);
	ft_malloc(0, 1);
	return (exit_status);
}
