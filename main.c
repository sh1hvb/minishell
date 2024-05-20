/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:55:08 by smarsi            #+#    #+#             */
/*   Updated: 2024/05/20 15:14:13 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		printf("========= end lexer\n");
		while (lex)
		{
			printf("value is :%s, type is : %c\n", lex->value, lex->type);
			lex = lex->next;
		}
		free(prompt);
	}
}

int	main(int ac, char *av[])
{
	if (ac > 1)
		ft_error("invalid number of params.\n", 126);
	(void) av;
	minishell();
	char *p = ft_malloc(1000, 0);
	p[0] = 'k';
	// ft_malloc(0, 1);
	return (0);
}
  