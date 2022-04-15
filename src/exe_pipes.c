/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 15:02:33 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/13 15:05:16 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_last_child(int prev_fd, int i, t_cmd_grp *cmd_grp, int *fd)
{
	int	redir;

	if (i == 0)
	{
		ft_putstr_fd("firstchild\n", g_data->log_fd);
		redir = redirections(cmd_grp->retokens);
		if (redir != 2 && redir != 3)
			utl_move_fd(fd[1], 1);
		ft_close(fd[0]);
	}
	else if (i == g_data->pipe_number)
	{
		ft_putstr_fd("lastchild\n", g_data->log_fd);
		redir = redirections(cmd_grp->retokens);
		if (redir != 1 && redir != 3)
			utl_move_fd(prev_fd, 0);
	}
}

void	middle_child(int prev_fd, t_cmd_grp *cmd_grp, int *fd)
{
	int	redir;

	ft_putstr_fd("middlechild\n", g_data->log_fd);
	redir = redirections(cmd_grp->retokens);
	if (redir != 1 && redir != 3)
		utl_move_fd(prev_fd, 0);
	if (redir != 2 && redir != 3)
		utl_move_fd(fd[1], 1);
	ft_close(fd[0]);
}

int	exe_pipes(t_list *cmd_grps_list)
{
	int			i;
	int			fd[2];
	int			status;
	static int	prev_fd;
	t_cmd_grp	*cmd_grp;

	g_data->log_fd = open("logfile", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	i = -1;
	while (++i <= g_data->pipe_number)
	{
		cmd_grp = cmd_grps_list->content;
		if (i != g_data->pipe_number)
			ft_pipe(fd);
		if (ft_fork() == 0)
		{
			if ((i == 0) || (i == g_data->pipe_number))
			{
				first_last_child(prev_fd, i, cmd_grp, fd);
			}
			else
				middle_child(prev_fd, cmd_grp, fd);
			if (exe_builtins(cmd_grp) == 1)
				exe_path(cmd_grp->args);
			exit(0);
		}
		else if (i == 0)
		{
			ft_close(fd[1]);
			prev_fd = fd[0];
		}
		else if (i == g_data->pipe_number)
			ft_close(prev_fd);
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
