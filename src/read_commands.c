/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:44:47 by leu-lee           #+#    #+#             */
/*   Updated: 2022/03/24 19:53:41 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execve_stuff(char *input)
{
	data->pipe_number = 0; // temp here
	if (data->pipe_number > 0)
		exec_pipes(input);
	if (fork() == 0)
		exec_path(input);
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
		if (ft_strncmp(split[0], data->builtins[i],
				ft_strlen(data->builtins[i])) == 0)
		{
			data->builtin_funcs[i](&split[1]);
			return ;
		}
		else
			execve_stuff(split[0]);
	}
	return ;
}
