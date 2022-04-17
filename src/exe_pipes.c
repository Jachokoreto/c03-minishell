/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatan <jatan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 15:02:33 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/17 12:15:35 by jatan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_last_child(int prev_fd, int i, t_cmd_grp *cmd_grp, int *fd)
{
	int	redir;

	if (i == 1)
	{
		redir = redirections(cmd_grp->retokens);
		if (redir != 2 && redir != 3)
			utl_move_fd(fd[1], 1);
		ft_close(fd[0]);
	}
	else if (i == 0)
	{
		redir = redirections(cmd_grp->retokens);
		if (redir != 1 && redir != 3)
			utl_move_fd(prev_fd, 0);
	}
}

void	middle_child(int prev_fd, t_cmd_grp *cmd_grp, int *fd)
{
	int	redir;

	redir = redirections(cmd_grp->retokens);
	if (redir != 1 && redir != 3)
		utl_move_fd(prev_fd, 0);
	if (redir != 2 && redir != 3)
		utl_move_fd(fd[1], 1);
	ft_close(fd[0]);
}

int	exe_pipes(t_list *cmd_grp_list, int pipe_num, t_data *g_data)
{
	int			i;
	int			fd[2];
	static int	prev_fd;
	t_cmd_grp	*cmd_grp;
	char		**envp;
	char		**path;

	i = -1;
	while (++i <= pipe_num)
	{
		cmd_grp = cmd_grp_list->content;
		if (i != pipe_num)
			ft_pipe(fd);
		if (ft_fork() == 0)
		{
			if (pipe_num > 0 && (i == 0 || i == pipe_num))
				first_last_child(prev_fd, i + 1 % pipe_num, cmd_grp, fd);
			else if (pipe_num > 0)
				middle_child(prev_fd, cmd_grp, fd);
			else
				redirections(cmd_grp->retokens);
			if (exe_builtins(cmd_grp, g_data) == 1)
			{
				path = ft_split(mini_getenv("PATH", g_data->envp), ':');
				envp = get_env_array(g_data);
				exe_path(cmd_grp->args, envp, path);
				free_str_array(path);
				free_str_array(envp);
			}
			exit(0);
		}
		else if (i == 0)
		{
			ft_close(fd[1]);
			prev_fd = fd[0];
		}
		else if (i == pipe_num)
			ft_close(prev_fd);
		else
		{
			ft_close(fd[1]);
			ft_close(prev_fd);
			prev_fd = fd[0];
		}
		cmd_grp_list = cmd_grp_list->next;
		while (waitpid(-1, NULL, 0) > 0)
			;
	}
	return (0);
}
