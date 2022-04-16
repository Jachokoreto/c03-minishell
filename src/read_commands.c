/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatan <jatan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:44:47 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/16 18:50:08 by jatan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	read_commands(t_list *cmd_grp_list, t_data *g_data, int pipe_num)
{
	// int			status;
	// t_cmd_grp	*cmd_grp;
	int			saved_fd[2];
	// char		**path;
	// char		**envp;

	saved_fd[0] = dup(0);
	saved_fd[1] = dup(1);
	if (cmd_grp_list == NULL)
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
