/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 19:54:08 by mchihab           #+#    #+#             */
/*   Updated: 2024/07/27 17:10:38 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	end_heredoc(char *line, char *delimiter)
{
	if (!line || ft_strcmp(line, delimiter) == 0)
	{
		if (!line)
		{
			ft_putstr_fd("\n", 2);
			ft_putstr_fd("minishell: warning: here-document delimited \
			by end-of-file (wanted `", 2);
			write(2, delimiter, ft_strlen(delimiter) - 1);
			ft_putendl_fd("')", 2);
		}
		free(line);
		delimiter = NULL;
		line = NULL;
		return (1);
	}
	return (0);
}

void	heredoc_read_and_put_mult(t_data *data, int fdp)
{
	char	*line;
	char	*delimiter;
	char	*tmp;

	delimiter = data->heredoc->delimiter;
	while (1)
	{
		line = readline(">");
		if (end_heredoc(line, delimiter))
			break ;
		if (line && data->heredoc && !data->heredoc->type)
			line = heredoc_expand(line);
		if (!data->heredoc->next)
		{
			tmp = ft_strjoin(line, "\n");
			if (data->next && !data->next->heredoc && !data->next->next
				&& data->next->cmd)
				ft_putstr_fd(tmp, fdp);
			else if (!data->next)
				ft_putstr_fd(tmp, fdp);
			free(tmp);
		}
		free(line);
	}
}

void	heredoc_mult(t_data *data)
{
	t_data	*p;
	char	*tmp_path;

	int (status), (pid), (fds);
	p = data;
	tmp_path = "/tmp/heredoc.txt";
	pid = fork();
	if (pid == -1)
		perror("fork");
	fds = open(tmp_path, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (!fds)
		err();
	signal(SIGQUIT, SIG_IGN);
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
