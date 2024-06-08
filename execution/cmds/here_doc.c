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
			if (!line || ft_strcmp(line, delimiter) == 0)
			{
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

void heredoc_mult(t_data *data)
{
	int	fds[2];	
	if (pipe(fds) == -1)
		perror("pipe");
	while(data)
	{
		heredoc_read_and_put(data, fds);
		data = data->next;
	}
	close(fds[1]);
	if (dup2(fds[0], 0) == -1)
		perror("dup2");

}