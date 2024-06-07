#include "../../minishell.h"

void heredoc_read_and_put(t_files *heredoc, int *fdp)
{
    char	*line;
	char	*delimiter;
	delimiter = ft_strjoin(heredoc->delimiter, "\n");
	while (1)
	{
		write(1, ">", 1);
		line = get_next_line(STDIN_FILENO);
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(delimiter);
			delimiter = NULL;
			free(line);
			line = NULL;
			exit(1);
		}
		ft_putstr_fd(line, fdp[1]);
		free(line);
	}
}
void	heredoc(t_data *data)
{
	int	fds[2];
	int	pid;
	if (pipe(fds) == -1)
		perror("pipe");
	pid = fork();
	if (pid == -1)
		perror("fork");
	if (!pid)
		heredoc_read_and_put(data->heredoc, fds);
	close(fds[1]);
	if (dup2(fds[0], 0) == -1)
		perror("dup2");
    wait(NULL);
}