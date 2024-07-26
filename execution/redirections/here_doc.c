#include "../../minishell.h"

int	end_heredoc(char *line, char *delimiter)
{
	if (!line || ft_strcmp(line, delimiter) == 0)
	{
		if (!line)
		{
			ft_putstr_fd("\n", 2);
			ft_putstr_fd("minishell: warning: here-document delimited\
			 by end-of-file (wanted `", 2);
			write(2, delimiter, ft_strlen(delimiter) - 1);
			ft_putendl_fd("')", 2);
		}
		free(delimiter);
		delimiter = NULL;
		free(line);
		line = NULL;
		return (1);
	}
	return (0);
}
void	heredoc_read_and_put_mult(t_data *data, int fdp)
{
	char	*line;
	char	*delimiter;

	delimiter = ft_strjoin(data->heredoc->delimiter, "\n");
	while (1)
	{
		write(2, ">", 1);
		line = get_next_line(STDIN_FILENO);
		if (line && data->heredoc && !data->heredoc->type)
			line = heredoc_expand(line);
		if (end_heredoc(line, delimiter))
			break ;
		if (!data->heredoc->next)
		{
			if (data->next && !data->next->heredoc && !data->next->next
				&& data->next->cmd)
				ft_putstr_fd(line, fdp);
			else if (!data->next)
				ft_putstr_fd(line, fdp);
		}
		free(line);
	}
}

void	heredoc_mult(t_data *data)
{
	t_data	*p;
	char	*tmp_path;

	int(status), (pid), (fds);
	p = data;
	tmp_path = "/tmp/heredoc.txt";
	pid = fork();
	if (pid == -1)
		perror("fork");
	fds = open(tmp_path, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (!fds)
		err();
	signal(SIGQUIT, sig_quit_heredoc);
	if (pid == 0)
		call_here_put(p, fds);
	waitpid(pid, &status, 0);
	env->exit_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		env->exit_status = WTERMSIG(status) + 128;
	if (env->exit_status == 130)
		env->signal_heredoc = 1;
	close(fds);
}
