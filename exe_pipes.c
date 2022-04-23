/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pipe_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 15:02:33 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/17 14:43:26 by jatan            ###   ########.fr       */
/*   Updated: 2022/04/19 14:06:02 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	first_last_child(int prev_fd, int i, t_cmd_grp *cmd_grp, int *fd)
{
	int	redir;

	if (i == 0)
	{
		// printf("testing1\n");
		redir = redirections(cmd_grp->retokens);
		if (redir != 2 && redir != 3)
			utl_move_fd(fd[1], 1);
		ft_close(fd[0]);
	}
	else
	{
		// printf("testing2\n");
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

void	parent_process(int prev_fd, int i, t_data *g_data, int *fd)
{
	if (i == 0)
	{
		ft_close(fd[1]);
		prev_fd = fd[0];
	}
	else if (i == g_data->pipe_num)
		ft_close(prev_fd);
	else
	{
		ft_close(fd[1]);
		ft_close(prev_fd);
		prev_fd = fd[0];
	}
}

int	exe_pipe_cmds(t_list *cmd_grp_list, t_data *g_data)
{
	int			i;
	int			status;
	int			fd[2];
	static int	prev_fd;
	t_cmd_grp	*cmd_grp;
	char		**envp;
	char		**path;

	i = -1;
	// printf("pipe_num %d\n", g_data->pipe_num);
	while (++i <= g_data->pipe_num)
	{
		cmd_grp = cmd_grp_list->content;
		if (i != g_data->pipe_num)
			ft_pipe(fd);
		if (ft_fork() == 0)
		{
			if (g_data->pipe_num > 0 && (i == 0 || i == g_data->pipe_num))
				first_last_child(prev_fd, i, cmd_grp, fd);
			else if (g_data->pipe_num > 0)
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
		else if (i == g_data->pipe_num)
			ft_close(prev_fd);
		else
		{
			ft_close(fd[1]);
			ft_close(prev_fd);
			prev_fd = fd[0];
		}
		cmd_grp_list = cmd_grp_list->next;
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
		{
			g_data->exit_status = WEXITSTATUS(status);
			// printf("Exit status was %d\n", g_data->exit_status);
		}
	}
	return (0);
}
