/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatan <jatan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:44:47 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/17 11:57:07 by jatan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	read_commands(t_list *cmd_grp_list, t_data *g_data, int pipe_num)
{
	int			status;
	t_cmd_grp	*cmd_grp;
	int			saved_fd[2];
	char		**path;
	char		**envp;

	saved_fd[0] = dup(0);
	saved_fd[1] = dup(1);
	if (cmd_grp_list == NULL)
		return ;
	if (pipe_num > 0)
		exe_pipes(cmd_grp_list, pipe_num, g_data);
	else
	{
		cmd_grp = cmd_grp_list->content;
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
		while (waitpid(-1, &status, 0) > 0)
			;
		// free_str_array(path);
		// free_str_array(envp);
	}
	utl_move_fd(saved_fd[1], 1);
	utl_move_fd(saved_fd[0], 0);
	return ;
}
