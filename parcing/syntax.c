
#include "../minishell.h"

void	valid_prompt(char *prompt)
{
	int (i), (flag), (flag2);
	flag = 0;
	flag2 = 0;
	i = 0;
	while (prompt[i])
	{
		if (prompt[i] == '\"' && !flag2)
		{
			if (flag == 0)
				flag = 1;
			else
				flag = 0;
		}
		else if (prompt[i] == '\'' && !flag)
		{
			if (flag2 == 0)
				flag2 = 1;
			else
				flag2 = 0;
		}
		i++;
	}
	if (flag == 1 || flag2 == 1)
		ft_error("Syntax Error. \n", 1);
}
