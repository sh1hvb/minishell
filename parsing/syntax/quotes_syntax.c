#include "../../minishell.h"

int	helper_line(int flag, int flag2)
{
	if (flag == 1)
		printf("minishell: unexpected EOF while looking for matching `\"'\n");
	if (flag2)
		printf("minishell: unexpected EOF while looking for matching `\''\n");
	if (flag2 | flag)
	{
		printf("minishell: syntax error: unexpected end of file \n");
		return (2);
	}
	return (0);
}

int	valid_quotes(char *prompt)
{
	int (i), (flag), (flag2);
	flag = 0;
	flag2 = 0;
	i = 0;
	while (prompt && prompt[i])
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
	return (helper_line(flag, flag2));
}
