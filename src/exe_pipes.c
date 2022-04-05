/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatan <jatan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 19:46:10 by leu-lee           #+#    #+#             */
/*   Updated: 2022/03/31 18:57:32 by jatan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	**get_pipes(void)
{
	int	**pipes;
	int	i;

	pipes = ft_calloc(g_data->pipe_number, sizeof(int *));
	i = 0;
	while (i < g_data->pipe_number)
	{
		pipes[i] = ft_calloc(2, sizeof(int));
		pipe(pipes[i]);
		i++;
	}
	return (pipes);
}

void	first_last_child(int **pipes, int i, char *input)
{
	int	fd_out;
	int	fd_in;

	if (i == 0)
	{
		fd_in = open("infile", O_RDONLY, 0777);
		dup2(fd_in, 0);
		close(fd_in);
		dup2(pipes[i][1], 1);
		close(pipes[i][1]);
		close(pipes[i][0]);
		exe_path(input);
	}
	if (i == g_data->pipe_number)
	{
		fd_out = open("outfile", O_CREAT | O_WRONLY| O_APPEND, 0644);
		dup2(pipes[i - 1][0], 0);
		close(pipes[i - 1][0]);
		close(pipes[i - 1][1]);
		dup2(fd_out, 1);
		close(fd_out);
		exe_path(input);
	}
}

void	middle_child(int **pipes, int i, char *input)
{
	dup2(pipes[i - 1][0], 0);
	close(pipes[i - 1][0]);
	dup2(pipes[i][1], 1);
	close(pipes[i][1]);
	close(pipes[i][0]);
	exe_path(input);
	// execve("/bin/ps", args2, envp);
}

void	parent_close_fd(int **pipes, int i)
{
	if (i == 0)
		close(pipes[i][1]);
	else if (i == g_data->pipe_number)
		close(pipes[i - 1][0]);
	else
	{
		close(pipes[i - 1][0]);
		close(pipes[i][1]);
	}
}

int	exe_pipes(char *input)
{
	int	i;
	int	process;
	int	**pipes;
	int	status;

	pipes = get_pipes();
	i = -1;
	while (++i <= g_data->pipe_number)
	{
		process = fork();
		if (process == 0)
		{
			if ((i == 0) || (i == g_data->pipe_number))
				first_last_child(pipes, i, input);
			else
				middle_child(pipes, i, input);
		}
		parent_close_fd(pipes, i);
		while (waitpid(-1, &status, 0) > 0)
			;
	}
	return (0);
}
