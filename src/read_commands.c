/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:44:47 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/11 10:52:59 by leu-lee          ###   ########.fr       */
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
	// int			i;
	t_cmd_grp	*cmd_grp;

	// loop_retokens(cmd_grp->retokens);
	cmd_grp = cmd_grp_list->content;
	// while (cmd_grp_list)
	// {
	// 	cmd_grp = cmd_grp_list->content;
	// 	i = -1;
	// 	while (++i < 7)
	// 	{
	// 		if (utl_strncmp(cmd_grp->args[0], g_data->builtins[i]) == 0)
	// 		{
	// 			// printf("builtin\n");
	// 			g_data->builtin_funcs[i](cmd_grp->args);
	// 			break ;
	// 		}
	// 	}
	// 	exe_pipes(cmd_grp_list);
	// 	cmd_grp_list = cmd_grp_list->next;
	// }
	if (g_data->pipe_number > 0)
		exe_pipes(cmd_grp_list);
	else
		exe_path(cmd_grp->args[0]);
	return ;
}
