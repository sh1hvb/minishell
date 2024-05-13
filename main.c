/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:55:08 by smarsi            #+#    #+#             */
/*   Updated: 2024/05/13 18:26:08 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(char *msg, int ext)
{
	printf("%s", msg);
	exit(ext);
}

int	main(int ac, char *av[])
{
	if (ac > 1)
		ft_error("invalid number of params.\n", 126);
	printf("parms : %s\n", av[1]);
}


// readline  
//  ls "-la > out" -a > out | << pp >> p < p 
// > |
// "
//


// ----------->    