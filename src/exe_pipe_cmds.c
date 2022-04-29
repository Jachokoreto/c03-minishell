/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pipe_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatan <jatan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 18:38:23 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/29 18:35:41 by jatan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exe_parent_proc(int i, int *fd, int pipe_num, int *prev_fd)
{
	if (i == 0)
	{
		ft_close(fd[1]);
		*prev_fd = fd[0];
	}
	else if (i == pipe_num)
		ft_close(*prev_fd);
	else
	{
		ft_close(fd[1]);
		ft_close(*prev_fd);
		*prev_fd = fd[0];
	}
}

static void	exe_child_proc(int prev_fd, int *fd, int child_num, int redir)
{
	if (child_num == FIRST)
	{
		if (redir != 2 && redir != 3)
			utl_move_fd(fd[1], 1);
		ft_close(fd[0]);
	}
	else if (child_num == LAST)
	{
		if (redir != 1 && redir != 3)
			utl_move_fd(prev_fd, 0);
	}
	else if (child_num == MIDDLE)
	{
		if (redir != 1 && redir != 3)
			utl_move_fd(prev_fd, 0);
		if (redir != 2 && redir != 3)
			utl_move_fd(fd[1], 1);
		ft_close(fd[0]);
	}
}

void	exe_proc(t_cmd_grp *cmd_grp, int i, int pipe_num, t_data *data)
{
	int			fd[2];
	static int	prev_fd;
	int			process;
	int			redir;

	if (i != pipe_num)
		ft_pipe(fd);
	g_exit = 0;
	process = ft_fork();
	if (process == 0)
	{
		redir = redirections(cmd_grp->retokens);
		if (pipe_num > 0 && (i == 0))
			exe_child_proc(prev_fd, fd, FIRST, redir);
		else if (pipe_num > 0 && (i == pipe_num))
			exe_child_proc(prev_fd, fd, LAST, redir);
		else if (pipe_num > 0)
			exe_child_proc(prev_fd, fd, MIDDLE, redir);
		exe_commands(cmd_grp, data, pipe_num);
		exit (0);
	}
	exe_parent_proc(i, fd, pipe_num, &prev_fd);
}

int	exe_pipe_cmds(t_list *cmd_grp_list, t_data *data, int pipe_num)
{
	int			i;
	int			status;
	t_cmd_grp	*cmd_grp;

	i = -1;
	while (++i <= pipe_num)
	{
		cmd_grp = cmd_grp_list->content;
		exe_proc(cmd_grp, i, pipe_num, data);
		cmd_grp_list = cmd_grp_list->next;
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			g_exit = WEXITSTATUS(status);
	}
	return (0);
}
