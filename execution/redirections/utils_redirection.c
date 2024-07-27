/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 20:07:35 by mchihab           #+#    #+#             */
/*   Updated: 2024/07/26 20:07:53 by mchihab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_input_redirection(t_data *data)
{
	t_files	*file;

	if (ft_input(data->redir_in))
		exit(1);
	file = ft_lstlast_file(data->redir_in);
	dup2(file->index, 0);
	close(file->index);
}

void	handle_output_redirection(t_data *data)
{
	t_files	*file;

	if (ft_output(data->redir_out))
		exit(1);
	file = ft_lstlast_file(data->redir_out);
	dup2(file->index, 1);
	close(file->index);
}

void	handle_append_redirection(t_data *data)
{
	t_files	*file;

	if (ft_append_file(data->append))
		exit(1);
	file = ft_lstlast_file(data->append);
	dup2(file->index, 1);
	close(file->index);
}

void	handle_process_redirections(t_data *data)
{
	if (data)
	{
		if (data->redir_in)
			handle_input_redirection(data);
		if (data->redir_out)
			handle_output_redirection(data);
		if (data->append)
			handle_append_redirection(data);
		handle_heredoc(data);
	}
}
