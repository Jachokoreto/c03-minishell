/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:44:47 by leu-lee           #+#    #+#             */
/*   Updated: 2022/03/29 17:58:21 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execve_stuff(char *input)
{
	g_data->pipe_number = 0; // temp here
	if (g_data->pipe_number > 0)
		exe_pipes(input);
	if (fork() == 0)
		exe_path(input);
}

void	read_commands(t_data *g_data, char *line)
{
	int		i;
	char	**split;

	// while (line[i] == 32 || (line[i] >= 9 && line[i] <= 13))
	// 	i++;
	split = ft_split(line, ' ');
	i = -1;
	while (++i < 7)
	{
		if (ft_strncmp(split[0], g_data->builtins[i],
				ft_strlen(split[0])) == 0)
		{
			g_data->builtin_funcs[i](&split[1]);
			return ;
		}
		else
			;// execve_stuff(split[0]);
	}
	return ;
}
