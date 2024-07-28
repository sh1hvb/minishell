/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 18:22:40 by mchihab           #+#    #+#             */
/*   Updated: 2024/07/28 18:22:41 by mchihab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp	*g_env = NULL;

int		pars_lstsize(t_data *lst);

t_data	*pars_lstnew(char *value, int quotes);
void	pars_lstclear(t_data **lst);
void	heredoc_lstadd_back(t_files **lst, t_files *new);
t_files	*heredoc_lstnew(char *value);
void	print_expand(t_lexer *lex_tmp);
void	print_parsing(t_data *data);
void	print_lexer(t_lexer *lex_tmp);

void	minishell(void)
{
	char	*prompt;
	t_lexer	*lex;
	t_data	*data;
	int		status;
	int		ex;

	status = 0;
	while (1)
	{
		(signal(SIGINT, sigint_handler), signal(SIGQUIT, SIG_IGN));
		prompt = NULL;
		lex = NULL;
		data = pars_lstnew(NULL, 0);
		prompt = readline("minishell$ ");
		(signal(SIGINT, sigint_int), signal(SIGQUIT, signal_quit));
		if (!prompt)
		{
			printf("exit\n");
			ft_malloc(0, 1);
			ex = g_env->exit_status;
			ft_lstclear_env(g_env);
			exit(ex);
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
			continue ;
		}
		lexer(prompt, &lex);
		status = check_syntax(lex);
		if (!status)
		{
			expand(prompt, &lex);
			heredoc_counter(lex);
			if (parsing(&lex, &data))
			{
				free(prompt);
				continue ;
			}
			process_cmd(data);
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
