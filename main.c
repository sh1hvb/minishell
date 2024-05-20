/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:55:08 by smarsi            #+#    #+#             */
/*   Updated: 2024/05/19 20:30:19 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data  *data;

void	minishell()
{
	char	*prompt;
	t_lexer  *lex;

	lex = malloc(sizeof(t_lexer));
	if (!lex)
		return;
	while (1)
	{
		prompt = readline("minishell$ ");
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
	minishell();
}
  