/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/03/21 14:44:47 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/18 13:19:31 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_one_cmd(t_cmd_grp *cmd_grp, t_data *g_data)
{
	char		**path;
	char		**envp;
	int			status;

	g_exit = 0;
	// printf("exit_status: %d\n", g_exit);
	if (exe_builtins(cmd_grp, g_data) == 1)
	{
		// printf("----fork----\n");
		if (ft_fork() == 0)
		{
			path = ft_split(mini_getenv("PATH", g_data->envp), ':');
			envp = get_env_array(g_data);
			exe_path(cmd_grp->args, envp, path);
			free_str_array(path);
			free_str_array(envp);
		}
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			g_exit = WEXITSTATUS(status);
	}
	// printf("exit_status: %d\n", g_exit);
}

void	executor(t_list *cmd_grp_list, t_data *g_data)
{
	// int			status;
	int			saved_fd[2];
	int			pipe_num;
	t_cmd_grp	*cmd_grp;

	saved_fd[0] = dup(0);
	saved_fd[1] = dup(1);
	pipe_num = ft_lstsize(g_data->cmd_grps) - 1;
	if (cmd_grp_list == NULL)
		return ;
	if (pipe_num > 0)
		exe_pipe_cmds(cmd_grp_list, g_data, pipe_num);
	else
	{
		cmd_grp = cmd_grp_list->content;
		if (redirections(g_data->tokens) != -1)
			exe_one_cmd(cmd_grp, g_data);
		return ;
		// free_str_array(path);
		// free_str_array(envp);
	}
	utl_move_fd(saved_fd[1], 1);
	utl_move_fd(saved_fd[0], 0);
}
