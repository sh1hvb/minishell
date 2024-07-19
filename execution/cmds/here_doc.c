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
			if(line && !data->heredoc->type && ft_strcmp(line, delimiter))
				line = heredoc_expand(line);
			if (!line || ft_strcmp(line, delimiter) == 0)
			{
                if (!line)
                {
                    ft_putstr_fd("\n", 2);
                    ft_putstr_fd("minishell: warning: here-document delimited by end-of-file (wanted `", 2);
                    write(2, delimiter, ft_strlen(delimiter) - 1);
                    ft_putendl_fd("')", 2);
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
	if(p->heredoc)
		return 1;
    else
	    return 0;
}
int check_heredoc_two(t_data * data)
{
	t_data *p;
	p = data ;
	while(p)
	{
        if(check_heredoc(p))
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


void heredoc_read_and_put_mult(t_data *data, int fdp)
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
                    ft_putstr_fd("minishell: warning: here-document delimited by end-of-file (wanted `", 2);
                    write(2, delimiter, ft_strlen(delimiter) - 1);
                    ft_putendl_fd("')", 2);
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
                    ft_putstr_fd(line, fdp);
                }
                else if (!data->next)
                {
                    ft_putstr_fd(line, fdp);
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
    char    *tmp_path = "/tmp/heredoc.txt";
    int fds;

    int status, pid;
   if ((pid = fork()) == -1)
        perror("fork");
    fds = open(tmp_path, O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if (!fds)
    {
        printf("error\n");
        exit (0);
    }
    if (pid == 0) 
    {
        while (p)
        {
			while(p->heredoc)
			{
                
            	heredoc_read_and_put_mult(p, fds);
				p->heredoc = p->heredoc->next;
			}
            p = p->next;
        }
        exit(0); 
    }
    while (waitpid(-1, &status, 0) != -1);
    env->exit_status = WEXITSTATUS(status);
    if (WIFSIGNALED(status))
        env->exit_status = WTERMSIG(status) + 128;
    close(fds);
}