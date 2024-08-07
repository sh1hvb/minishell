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

void    print_expand(t_lexer *lex_tmp)
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
    int i = 0;
    printf("\n#######################  parsing #######################\n");
    while (data)
	{
		printf("\n\n#######################  NODE : %d  #################################\n", i);
        printf("last_file : %d\n", data->last_file);
		printf("cmd is :%s\n", data->cmd);
        while (data->args && data->args[i])
        {
            printf("args[%d] = %s, ", i, data->args[i]);
            i++;
        }
        printf("\n");
        i = 0;
		printf("-------------------------- IN_FILE --------------------------------\n");
		while (data->redir_in)
        {
            printf("in_file num : %d, file_name : %s ", data->redir_in->index, data->redir_in->delimiter);
            data->redir_in = data->redir_in->next;
            printf("\n");
        }
		printf("-------------------------- OUT_FILE --------------------------------\n");
		while (data->redir_out)
        {
            printf("out_file num : %d, file_name : %s ", data->redir_out->index, data->redir_out->delimiter);
            data->redir_out = data->redir_out->next;
            printf("\n");
        }
		printf("-------------------------- HEREDOC --------------------------------\n");
        while (data->heredoc)
        {
            printf("heredoc num : %d, delimiter : %s  , type = %d",data->heredoc->index, data->heredoc->delimiter, data->heredoc->type);
            data->heredoc = data->heredoc->next;
            printf("\n");
        }
		printf("-------------------------- APPEND --------------------------------\n");
		while (data->append)
        {
            printf("Append num : %d, delimiter : %s  ", data->append->index, data->append->delimiter);
            data->append = data->append->next;
            printf("\n");
        }
		data = data->next;
        i++;
	}
}