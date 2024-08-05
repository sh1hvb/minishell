/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_single.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 20:02:20 by mchihab           #+#    #+#             */
/*   Updated: 2024/08/03 23:31:26 by mchihab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	handle_file_redirections(t_data *data)
{
	if (data->append && ft_append_file(data->append))
		return (1);
	if (data->redir_in && ft_input(data->redir_in))
		return (1);
	if (data->redir_out && ft_output(data->redir_out))
		return (1);
	return (0);
}

void	setup_redirections(t_data *data)
{
	int	index;

	if (ft_lstlast_file(data->append))
	{
		index = ft_lstlast_file(data->append)->index;
		safe_dup2(index, 1);
		close(index);
	}
	if (ft_lstlast_file(data->redir_out))
	{
		index = ft_lstlast_file(data->redir_out)->index;
		safe_dup2(index, 1);
		close(index);
	}
	if (ft_lstlast_file(data->redir_in))
	{
		index = ft_lstlast_file(data->redir_in)->index;
		if (data->last_file == 1)
			safe_dup2(index, 0);
		close(index);
	}
}

void	close_file_descriptors(t_data *data)
{
	if (ft_lstlast_file(data->redir_in)
		&& ft_lstlast_file(data->redir_in)->index)
		close(ft_lstlast_file(data->redir_in)->index);
	if (ft_lstlast_file(data->redir_out)
		&& ft_lstlast_file(data->redir_out)->index)
		close(ft_lstlast_file(data->redir_out)->index);
	if (ft_lstlast_file(data->heredoc) && ft_lstlast_file(data->heredoc)->index)
		close(ft_lstlast_file(data->heredoc)->index);
}
