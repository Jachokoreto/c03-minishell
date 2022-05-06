/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 16:40:15 by leu-lee           #+#    #+#             */
/*   Updated: 2022/05/06 11:03:27 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Execve is done according to the PATH, execve will keep running until
 * a command can be run or if no command is found. When no command is found, 
 * an error message will be prompt to indicate that.
 */

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
			execve(cmd, input, envp);
			free(cmd);
		}
	}
	ft_putstr_fd(input[0], 2);
	if (input[0] != NULL)
		exit(utl_error(": command not found\n", 127));
	exit(0);
}

/**
 * Execve is done here. Before that, the PATH is checked whether or not if it
 * exist or not. The commands cannot be run if PATH does not exist. Else if it
 * exists, the input is passed into exe_path.
 */

void	exe_execve(t_cmd_grp *cmd_grp, t_data *data)
{
	char	**envp;
	char	**path;
	char	*mini_env;

	signal(SIGINT, SIG_DFL);
	mini_env = mini_getenv("PATH", data->envp);
	envp = get_env_array(data);
	if (mini_env == NULL)
	{
		execve(cmd_grp->args[0], cmd_grp->args, envp);
		ft_putstr_fd(cmd_grp->args[0], 2);
		free_str_array(envp);
		exit(utl_error(": No such file or directory\n", 1));
	}
	path = ft_split(mini_env, ':');
	exe_path(cmd_grp->args, envp, path);
	free_str_array(path);
	free_str_array(envp);
}

/**
 * There are 4 ways the program can run.
 * 1. One command group with builtins
 * --- The program does not need to fork.
 * 2. One command group without builtins
 * --- The program needs to fork.
 * 3. More than one command group with builtins
 * --- The program needs to fork. 
 * 4. More than one command group without builtins
 * --- The program needs to fork.
 */

void	exe_commands(t_cmd_grp *cmd_grp, t_data *data, int pipe_num)
{
	int	status;

	if (pipe_num == 0)
	{
		g_exit = 0;
		if (exe_builtins(cmd_grp, data) == 1)
		{
			if (ft_fork() == 0)
			{
				exe_execve(cmd_grp, data);
				exit(1);
			}
			waitpid(-1, &status, 0);
			if (WIFEXITED(status))
				g_exit = WEXITSTATUS(status);
		}
	}
	else
	{
		if (exe_builtins(cmd_grp, data) == 1)
			exe_execve(cmd_grp, data);
	}
}
