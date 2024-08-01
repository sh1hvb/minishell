/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 19:54:08 by mchihab           #+#    #+#             */
/*   Updated: 2024/08/01 14:35:36 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	end_heredoc(char *line, char *delimiter)
{
	if (!line || ft_strcmp(line, delimiter) == 0)
	{
		if (!line)
		{
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
			ft_putstr_fd(tmp, fdp);
			free(tmp);
		}
		free(line);
	}
}

void	heredoc_mult(t_data *data)
{
	t_data	*p;

	int (status), (pid);
	p = data;
	pid = fork();
	if (pid == -1)
		perror("fork");
	(signal(SIGQUIT, SIG_IGN), signal(SIGINT, SIG_IGN));
	if (pid == 0)
	{
		call_here_put(p);
	}
	waitpid(pid, &status, 0);
	g_env->exit_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		g_env->exit_status = WTERMSIG(status) + 128;
	if (g_env->exit_status == 130)
		g_env->signal_heredoc = 1;
}
