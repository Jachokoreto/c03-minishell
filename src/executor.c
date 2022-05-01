/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 17:17:21 by leu-lee           #+#    #+#             */
/*   Updated: 2022/05/01 12:00:06 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * The start of the execution of what have been parsed.
 * The fd input and output of the parent process will be saved temporarily.
 * This is done so that the builtins can be run without any child process
 * assuming there is only one command group.
 * If there is more than one command group, pipes will be used to transfer
 * the output to the child processes.
 */

void	executor(t_list *cmd_grp_list, t_data *data)
{
	int			saved_fd[2];
	t_cmd_grp	*cmd_grp;
	int			pipe_num;

	signal(SIGINT, SIG_IGN);
	saved_fd[0] = dup(0);
	saved_fd[1] = dup(1);
	pipe_num = ft_lstsize(data->cmd_grps) - 1;
	if (cmd_grp_list == NULL)
		return ;
	if (pipe_num > 0)
		exe_pipe_cmds(cmd_grp_list, data, pipe_num);
	else
	{
		cmd_grp = cmd_grp_list->content;
		if (redirections(data->tokens) != -1)
			exe_commands(cmd_grp, data, pipe_num);
	}
	utl_move_fd(saved_fd[1], 1);
	utl_move_fd(saved_fd[0], 0);
}
