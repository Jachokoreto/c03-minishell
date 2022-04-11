/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 15:02:33 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/11 10:37:41 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	loop_builtins(t_cmd_grp *cmd_grp)
{
	int	i;

	i = -1;
	while (++i < 7)
	{
		if (utl_strncmp(cmd_grp->args[0], g_data->builtins[i]) == 0)
		{
			g_data->builtin_funcs[i](cmd_grp->args);
			return (0);
		}
	}
	return (1);
}

void	loop_retokens(t_list *retokens)
{
	t_token	*token;
	int		fd_in;
	int		fd_out;

	fd_out = 0;
	fd_in = 0;
	while (retokens)
	{
		token = retokens->content;
		if (token->type == outfile1)
		{
			if (!fd_out)
				ft_close(fd_out);
			fd_out = ft_open(token->value, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		}
		if (token->type == outfile2)
		{
			if (!fd_out)
				ft_close(fd_out);
			fd_out = ft_open(token->value, O_WRONLY | O_CREAT | O_APPEND, 0666);
		}
		if (token->type == infile)
		{
			if (!fd_in)
				ft_close(fd_in);
			fd_in = ft_open(token->value, O_RDONLY, 0666);
		}
		if (token->type == delim)
		{
			if (!fd_in)
				ft_close(fd_in);
			fd_in = heredoc(token->value);
		}
		retokens = retokens->next;
	}
	if (fd_out != 0)
		utl_move_fd(fd_out, 1);
	if (fd_in != 0)
		utl_move_fd(fd_in, 0);
}

void	first_last_child(int prev_fd, int i, t_cmd_grp *cmd_grp, int *fd)
{
	(void)cmd_grp;
	(void)fd;
	if (i == 0)
	{
		printf("firstchild\n");
		ft_dup2(fd[1], 1);
		ft_close(fd[1]);
		ft_close(fd[0]);
		printf("testing\n");
		//loop_retokens(cmd_grp->retokens);
		// exe_path(cmd_grp->args);
	}
	else if (i == g_data->pipe_number)
	{
		printf("lastchild\n");
		ft_dup2(prev_fd, 0);
		ft_close(prev_fd);
		//loop_retokens(cmd_grp->retokens);
		// exe_path(cmd_grp->args);
	}
}

void	middle_child(int prev_fd, t_cmd_grp *cmd_grp, int *fd)
{
	(void)cmd_grp;
	printf("middlechild\n");
	ft_dup2(fd[1], 1);
	ft_close(fd[1]);
	ft_dup2(prev_fd, 0);
	ft_close(prev_fd);
	ft_close(fd[0]);
	// exe_path(cmd_grp->args);
}

int	exe_pipes(t_list *cmd_grps_list)
{
	int			i;
	int			process;
	int			fd[2];
	int			status;
	static int	prev_fd;
	t_cmd_grp	*cmd_grp;

	i = -1;
	printf("g_data->cmd_grps: %d\n", g_data->pipe_number);
	while (++i <= g_data->pipe_number)
	{
		// printf("cmd_grp %s\n", cmd_grp->args[0]);
		cmd_grp = cmd_grps_list->content;
		if (i != g_data->pipe_number)
			ft_pipe(fd);
		process = ft_fork();
		if (process == 0)
		{
			printf("i: %d\n", i);
			if ((i == 0) || (i == g_data->pipe_number))
			{
				first_last_child(prev_fd, i, cmd_grp, fd);
			}
			else
				middle_child(prev_fd, cmd_grp, fd);
			if (loop_builtins(cmd_grp) == 1)
				exe_path(cmd_grp->args);
				
		}
		else if (i == 0)
		{
			ft_close(fd[1]);
			prev_fd = fd[0];
		}
		else if (i == g_data->pipe_number)
		{
			ft_close(prev_fd);
		}
		else
		{
			ft_close(fd[1]);
			ft_close(prev_fd);
			prev_fd = fd[0];
		}
		cmd_grps_list = cmd_grps_list->next;
		while (waitpid(-1, &status, 0) > 0)
			;
	}
	return (0);
}
