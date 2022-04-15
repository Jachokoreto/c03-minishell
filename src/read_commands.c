/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:44:47 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/15 14:27:02 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	dup_files(void)
// {
// 	g_data->fd_type[3] = dup(1);
// 	close(g_data->fd_type[3]);
// 	dup2(g_data->ft_type[1] ,1);

// }

// void	execve_cmds(t_cmd_grp *cmd_grp)
// {
// 	int	status;
// 	// temp here
// 	// if (g_data->pipe_number > 0) // gotta consider process = 0
// 	// 	exe_pipes(cmd_grp);
// 	while (waitpid(-1, &status, 0) > 0)
// 		;
// }

void	read_commands(t_list *cmd_grp_list)
{
	int			status;
	t_cmd_grp	*cmd_grp;
	int			saved_fd[2];

	saved_fd[0] = dup(0);
	saved_fd[1] = dup(1);
	cmd_grp = cmd_grp_list->content;
	if (cmd_grp->args[0] == NULL)
		return ;
	if (g_data->pipe_number > 0)
		exe_pipes(cmd_grp_list);
	else
	{
		redirections(cmd_grp->retokens);
		if (exe_builtins(cmd_grp) == 1)
		{
			// printf("Non-builtins\n");
			if (ft_fork() == 0)
				exe_path(cmd_grp->args);
		}
		// printf("cmd: %s\n", cmd_grp->args[0]);
		while (waitpid(-1, &status, 0) > 0)
					;
	}
	utl_move_fd(saved_fd[1], 1);
	utl_move_fd(saved_fd[0], 0);
	return ;
}
