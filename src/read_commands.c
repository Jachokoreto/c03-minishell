/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:44:47 by leu-lee           #+#    #+#             */
/*   Updated: 2022/03/23 11:27:02 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execve_stuff(char *input)
{
	char	**path;
	char	*cmd = NULL;
	char	*argvec[] = { cmd, NULL};
	char	*envVec[] = {"CSC220=Linux", "SECRET=Study Hard", "HELLO=BYE"};
	int		i;

	if (fork() == 0)
	{
		path = ft_split(mini_getenv("PATH"), ':');
		i = 0;
		while (path)
		{
			cmd = join_key_value(path[i++], input, '/');
			argvec[0] = cmd;
			// printf("cmd :%s, input: %s\n", argvec[0], argvec[1]);
			// printf("start of execve call %s:\n", cmd);
			// printf("--------------------------------------------------\n");
			if (execve(cmd, argvec, envVec) == -1)
			{
				// perror("Could not execute execve");
			}
			// printf("Oops, something went wrong!\n\n");
		}
	}
}

void	read_commands(t_data *data, char *line)
{
	int		i;
	char	**split;

	// while (line[i] == 32 || (line[i] >= 9 && line[i] <= 13))
	// 	i++;
	split = ft_split(line, ' ');
	i = -1;
	while (++i < 7)
	{
		if (ft_strncmp(split[0], data->builtins[i], ft_strlen(data->builtins[i])) == 0)
		{
			data->builtin_funcs[i](&split[1]);
			return ;
		}
	}
	execve_stuff(split[0]);
	return ;
}
