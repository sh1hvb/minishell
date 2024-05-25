#include "minishell.h"

void    print_lexer(t_lexer *lex_tmp)
{
    printf("\n#######################  lexer #######################\n");
    while (lex_tmp)
	{
		printf("value is :%s, type is : %c, in_quotes : %d\n", \
		lex_tmp->value, lex_tmp->type, lex_tmp->in_quotes);
		lex_tmp = lex_tmp->next;
	}
}

void    print_exand(t_lexer *lex_tmp)
{
    printf("\n#######################  expand #######################\n");
    while (lex_tmp)
	{
		printf("value is :%s, type is : %c, in_quotes : %d\n", \
		lex_tmp->value, lex_tmp->type, lex_tmp->in_quotes);
		lex_tmp = lex_tmp->next;
	}
}

void    print_parsing(t_data *data)
{
    printf("\n#######################  parsing #######################\n");
    while (data)
	{
        int i = 0;
		printf("################  NODE : %d  ##########\n", i);
		printf("value is :%s\n", data->cmd);
		printf("in_file : %s, out_file : %s\n", \
		data->redir_in, data->redir_out);
        while (data->heredoc_head)
        {
            printf("heredoc num : %d, delimiter : %s  ", data->heredoc_head->heredocs_index, data->heredoc_head->delimiter);
            data->heredoc_head = data->heredoc_head->next;
            printf("\n");
        }
		data = data->next;
	}
}