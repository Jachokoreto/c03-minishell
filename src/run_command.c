/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatan <jatan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:44:47 by leu-lee           #+#    #+#             */
/*   Updated: 2022/03/23 20:50:48 by jatan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_str_array(char **str)
{
	while (*str)
	{
		free(*str);
		str++;
	}
	free(str);
}

void	execve_stuff(char **arg_vec)
{
	char	**path;
	char	*cmd;
	char	**env_vec;
	int		i;

	env_vec = get_env_array();
	if (fork() == 0)
	{
		path = ft_split(mini_getenv("PATH"), ':');
		i = 0;
		while (path[i])
		{
			cmd = join_key_value(path[i++], arg_vec[0], '/');
			arg_vec[0] = cmd;
			// printf("cmd :%s, input: %s\n", argvec[0], argvec[1]);
			// printf("start of execve call %s:\n", cmd);
			// printf("--------------------------------------------------\n");
			if (execve(cmd, arg_vec, env_vec) == -1)
			{
				perror("Could not execute execve");
			}
			free(cmd);
			// printf("Oops, something went wrong!\n\n");
		}
		printf("Function unvailable\n");
		exit(0);
	}
}

void	run_command(t_data *g_data)
{
	int		i;
	char	**split;

	split = NULL;
	i = -1;
	while (++i < 7)
	{
		if (ft_strncmp(split[0], g_data->builtins[i], ft_strlen(g_data->builtins[i])) == 0)
		{
			g_data->builtin_funcs[i](&split[1]);
			return ;
		}
	}
	execve_stuff(&split[0]);
	return ;
}
