/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 16:40:15 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/23 16:30:51 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_path(char **input, char **envp, char **path)
{
	int		i;
	char	*cmd;

	if (execve(input[0], input, envp) == -1)
	{
		i = 0;
		while (path[i])
		{
			cmd = join_key_value(path[i++], input[0], '/');
			// g_exit = 0;
			execve(cmd, input, envp);
			free(cmd);
		}
	}
	ft_putstr_fd(input[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	g_exit = 127;
	exit(g_exit);
}

void	exe_commands(t_cmd_grp *cmd_grp, t_data *g_data, int pipe_num)
{
	char	**envp;
	char	**path;

	(void)pipe_num;
	if (exe_builtins(cmd_grp, g_data) == 1)
	{
		path = ft_split(mini_getenv("PATH", g_data->envp), ':');
		envp = get_env_array(g_data);
		exe_path(cmd_grp->args, envp, path);
		free_str_array(path);
		free_str_array(envp);
	}
}
