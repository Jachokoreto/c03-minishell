/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pipe_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 18:38:23 by leu-lee           #+#    #+#             */
/*   Updated: 2022/05/01 12:08:21 by leu-lee          ###   ########.fr       */
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

/**
 * All piping and redirections occur here. Pipe is also done if it is not the
 * last child because the last child does not need to pipe.
 * The duping and redirection is done based on what type of child process it it
 * is. For eg. cat < infile | wc -l | grep hi
 * cat < infile will be done as a first child
 * wc -l  will be done as a middle child  
 * grep hi will be done as a last child
 */

int	exe_proc(t_cmd_grp *cmd_grp, int i, int pipe_num, t_data *data)
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
		signal(SIGINT, SIG_DFL);
		redir = redirections(cmd_grp->retokens);
		if (pipe_num > 0 && (i == 0))
			exe_child_proc(prev_fd, fd, FIRST, redir);
		else if (pipe_num > 0 && (i == pipe_num))
			exe_child_proc(prev_fd, fd, LAST, redir);
		else if (pipe_num > 0)
			exe_child_proc(prev_fd, fd, MIDDLE, redir);
		exe_commands(cmd_grp, data, pipe_num);
		exit(0);
	}
	exe_parent_proc(i, fd, pipe_num, &prev_fd);
	return (process);
}

/**
 * Pid is malloc-ed to the number of command groups there are. Each pid will
 * then enter the exe_proc function where all piping and redirection happens.
 * The parent will wait for all child processes to end before return back to 
 * its readline prompt.
 */

int	exe_pipe_cmds(t_list *cmd_grp_list, t_data *data, int pipe_num)
{
	int			i;
	int			status;
	t_cmd_grp	*cmd_grp;
	int			*pid;

	pid = ft_calloc(pipe_num + 1, sizeof(int));
	i = -1;
	while (++i <= pipe_num)
	{
		cmd_grp = cmd_grp_list->content;
		pid[i] = exe_proc(cmd_grp, i, pipe_num, data);
		cmd_grp_list = cmd_grp_list->next;
	}
	i = -1;
	while (++i <= pipe_num)
	{
		waitpid(pid[i], &status, 0);
		if (WIFEXITED(status))
			g_exit = WEXITSTATUS(status);
	}
	free(pid);
	return (0);
}
