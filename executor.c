/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:44:47 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/18 13:19:31 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_one_cmd(t_list *cmd_grp_list, t_data *g_data)
{
	t_cmd_grp	*cmd_grp;
	char		**path;
	char		**envp;

	cmd_grp = cmd_grp_list->content;
	redirections(g_data->tokens);
	if (exe_builtins(cmd_grp, g_data) == 1)
	{
		if (ft_fork() == 0)
		{
			path = ft_split(mini_getenv("PATH", g_data->envp), ':');
			envp = get_env_array(g_data);
			exe_path(cmd_grp->args, envp, path);
			free_str_array(path);
			free_str_array(envp);
		}
	}
}

void	executor(t_list *cmd_grp_list, t_data *g_data)
{
	int			status;
	int			saved_fd[2];
	int			pipe_num;

	saved_fd[0] = dup(0);
	saved_fd[1] = dup(1);
	if (cmd_grp_list == NULL)
		return ;
	pipe_num = ft_lstsize(g_data->cmd_grps) - 1;
	// printf("g_data->pipe_num: %d\n", g_data->pipe_num);
	if (pipe_num > 0)
		exe_pipe_cmds(cmd_grp_list, g_data);
	else
	{
		exe_one_cmd(cmd_grp_list, g_data);
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			g_data->exit_status = WEXITSTATUS(status);
		// printf("Exit status was %d\n", g_data->exit_status);
		// free_str_array(path);
		// free_str_array(envp);
	}
	utl_move_fd(saved_fd[1], 1);
	utl_move_fd(saved_fd[0], 0);
	return ;
}
