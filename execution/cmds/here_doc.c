#include "../../minishell.h"

void heredoc_read_and_put(t_data *data, int *fdp)
{
    char	*line;
	char	*delimiter;
	while(data->heredoc)
	{
		delimiter = ft_strjoin(data->heredoc->delimiter, "\n");
		while (1)
		{
			write(1, ">", 1);
			line = get_next_line(STDIN_FILENO);
			if(line && !data->heredoc->type)
				line = heredoc_expand(line);
			if (!line || ft_strcmp(line, delimiter) == 0)
			{
                if (!line)
                {
                    ft_putstr_fd("\n", 2);
                    ft_putendl_fd("minishell: warning: here-document at line 126 delimited by end-of-file", 2);
                }
				free(delimiter);
				// delimiter = NULL;
				free(line);
				// line = NULL;
				break;
			}
			if(!data->heredoc->next)
				ft_putstr_fd(line, fdp[1]);
			free(line);
		}
		data->heredoc = data->heredoc->next;
	}
}
int check_heredoc(t_data * data)
{
	t_data *p;
	p = data ;
	while(p)
	{
		if(p->heredoc)
			return 1;
		p= p->next;
	}
	return 0;
}
void	heredoc(t_data *data)
{
	int	fds[2];	
	if (pipe(fds) == -1)
		perror("pipe");
	heredoc_read_and_put(data, fds);
	close(fds[1]);
	if (dup2(fds[0], 0) == -1)
		perror("dup2");

}


void heredoc_read_and_put_mult(t_data *data, int *fdp)
{
    char *line;
    char *delimiter;

    // while (data->heredoc)
    // {
        delimiter = ft_strjoin(data->heredoc->delimiter, "\n");
		
        while (1)
        {
            write(2, ">", 1);
            line = get_next_line(STDIN_FILENO);
            if (line && data->heredoc && !data->heredoc->type)
                line = heredoc_expand(line);
            if (!line || ft_strcmp(line, delimiter) == 0)
            {
                if (!line)
                {
                    ft_putstr_fd("\n", 2);
                    ft_putendl_fd("minishell: warning: here-document at line 126 delimited by end-of-file", 2);
                }
                free(delimiter);
				// delimiter =NULL;
                free(line);
				// line = NULL;
                break;
            }
            if (!data->heredoc->next)
            {
                if (data->next && !data->next->heredoc && !data->next->next && data->next->cmd)
                {
                    ft_putstr_fd(line, fdp[1]);
                }
                else if (!data->next)
                {
                    ft_putstr_fd(line, fdp[1]);
                }
            }
            free(line);
        // }
        // data->heredoc = data->heredoc->next;
    }
}

void heredoc_mult(t_data *data)
{
    t_data *p = data;
    int fdp[2];
    pipe(fdp);

    int pid = fork();
    if (pid == 0) 
    {
        close(fdp[0]);
        while (p)
        {
			while(p->heredoc)
			{
            	heredoc_read_and_put_mult(p, fdp);
				p->heredoc = p->heredoc->next;
			}
        	close(fdp[0]);
            // exec(p);
            if (dup2(fdp[1], STDOUT_FILENO) == -1)
                perror("dup2");
            p = p->next;
        }
        exit(0); 
    }
    else if (pid > 0)
    {
        // close(fdp[1]);
        // waitpid(-1, &status, 0); 
		close(fdp[1]);
        if (dup2(fdp[0], STDIN_FILENO) == -1)
            perror("dup2");
        close(fdp[0]);
    }
    else
    {
        perror("fork");
    }
}
