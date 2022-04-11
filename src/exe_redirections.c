/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 15:33:02 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/11 18:55:54 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_output(t_token *token, int fd_out)
{
	if (token->type == outfile1)
	{
		if (fd_out != 0)
			ft_close(fd_out);
		fd_out = ft_open(token->value, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	}
	else if (token->type == outfile2)
	{
		if (fd_out != 0)
			ft_close(fd_out);
		fd_out = ft_open(token->value, O_WRONLY | O_CREAT | O_APPEND, 0666);
	}
	return (fd_out);
}

int	redir_input(t_token *token, int fd_in)
{
	if (token->type == infile)
	{
		if (fd_in != 0)
			ft_close(fd_in);
		fd_in = ft_open(token->value, O_RDONLY, 0666);
	}
	else if (token->type == delim)
	{
		if (fd_in != 0)
			ft_close(fd_in);
		fd_in = heredoc(token->value);
	}
	return (fd_in);
}

int	redirections(t_list *retokens)
{
	t_token	*token;
	int		fd_in;
	int		fd_out;

	fd_out = 0;
	fd_in = 0;
	while (retokens)
	{
		token = retokens->content;
		fd_in = redir_input(token, fd_in);
		fd_out = redir_output(token, fd_out);
		retokens = retokens->next;
	}
	if (fd_out != 0)
		utl_move_fd(fd_out, 1);
	if (fd_in != 0)
		utl_move_fd(fd_in, 0);
	return ((fd_in > 0) * 1 + (fd_out > 0) * 2);
}
