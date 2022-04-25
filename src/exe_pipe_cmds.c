/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pipe_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 18:38:23 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/24 16:25:39 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_parent_proc(int i, int *fd, int pipe_num, int *prev_fd)
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

void	exe_proc(t_cmd_grp *cmd_grp, int i, int pipe_num, t_data *g_data)
{
	int			fd[2];
	static int	prev_fd;
	int			process;

	if (i != pipe_num)
		ft_pipe(fd);
	g_exit = 0;
	process = ft_fork();
	if (process == 0)
	{
		if (pipe_num > 0 && (i == 0))
			first_child(cmd_grp, fd);
		else if (pipe_num > 0 && (i == pipe_num))
			last_child(prev_fd, cmd_grp);
		else if (pipe_num > 0)
			middle_child(prev_fd, cmd_grp, fd);
		else
			redirections(cmd_grp->retokens);
		exe_commands(cmd_grp, g_data, pipe_num);
		exit(0);
	}
	exe_parent_proc(i, fd, pipe_num, &prev_fd);
}

int	exe_pipe_cmds(t_list *cmd_grp_list, t_data *g_data, int pipe_num)
{
	int			i;
	int			status;
	t_cmd_grp	*cmd_grp;

	i = -1;
	while (++i <= pipe_num)
	{
		cmd_grp = cmd_grp_list->content;
		exe_proc(cmd_grp, i, pipe_num, g_data);
		cmd_grp_list = cmd_grp_list->next;
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			g_exit = WEXITSTATUS(status);
	}
	return (0);
}
