/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:44:47 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/08 16:17:09 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execve_stuff(char *input)
{
	int	process;
	int	status;

	process = fork();
	g_data->pipe_number = 0; // temp here
	if (g_data->pipe_number > 0) // gotta consider process = 0
		exe_pipes(input);
	else if (process == 0)
		exe_path(input);
	while (waitpid(-1, &status, 0) > 0)
		;
}

void	read_commands(t_data *g_data, char *line)
{
	int		i;
	int		redir_out = 1; // TEMP
	int		saved_stdout;
	int		fd_out;
	char	**split;

	split = ft_split(line, ' ');
	i = -1;
	while (++i < 7)
	{	
		if (ft_strncmp(split[0], g_data->builtins[i],
				ft_strlen(g_data->builtins[i])) == 0)
		{
			if (redir_out > 0)
			{
				// temp implementation
				saved_stdout = dup(1);
				fd_out = open("tempfile", O_WRONLY | O_CREAT | O_TRUNC,
						0666);
				dup2(fd_out, 1);
				close(fd_out);
				g_data->builtin_funcs[i](&split[1]);
				dup2(saved_stdout, 1);
				close(saved_stdout);
			}
			else
				g_data->builtin_funcs[i](&split[1]);
			return ;
		}
	}
	execve_stuff(split[0]);
	return ;
}
