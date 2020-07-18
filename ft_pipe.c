/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavileo <mavileo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 11:57:19 by mavileo           #+#    #+#             */
/*   Updated: 2020/07/18 13:09:11 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		exec_command(t_list *token, t_fds *fds, int status)
{
	(void)status;
	if (!fork())
	{
		close(fds->pipe[0]);
		if (dup2(fds->pipe[1], 1) == -1)
			return (1);
		close(fds->pipe[1]);
		ft_command(token, fds);
	}
	else
	{
		close(fds->pipe[1]);
		if (dup2(fds->save_stdout, 1) == -1)
			return (1);
		if (dup2(fds->save_stdin, 0) == -1)
			return (1);
		if (dup2(fds->pipe[0], 0) == -1)
			return (1);
		close(fds->pipe[0]);
		ft_pipe(token->next->next, fds);
	}
	return (0);
}

int		ft_pipe(t_list *token, t_fds *fds)
{
	static int	count = 0;
	int			status = 0;
//	int			pid;

	if (!count)
		token = token->prev;
	if (!count || (token->next && ((t_token *)token->next->content)->type
		== PIPE))
	{
		count++;
		if (pipe(fds->pipe) == -1)
			return (1);
		if (exec_command(token, fds, status))
			exit(1);
	}
	else
	{
		write(1, ft_itoa(count), strlen(ft_itoa(count)));
		ft_command(token, fds);
	}
	exit(0);
	return (0);
}
