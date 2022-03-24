/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 19:46:10 by leu-lee           #+#    #+#             */
/*   Updated: 2022/03/24 19:53:02 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	**get_pipes(void)
{
	int	**pipes;
	int	i;

	pipes = malloc(sizeof(int *) * data->pipe_number);
	i = 0;
	while (i < data->pipe_number)
	{
		pipes[i] = malloc(sizeof(int) * 2);
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
		exec_path(input);
	}
	if (i == data->pipe_number)
	{
		fd_out = open("outfile", O_CREAT | O_WRONLY| O_APPEND, 0644);
		dup2(pipes[i - 1][0], 0);
		close(pipes[i - 1][0]);
		close(pipes[i - 1][1]);
		dup2(fd_out, 1);
		close(fd_out);
		exec_path(input);
	}
}

void	middle_child(int **pipes, int i, char *input)
{
	dup2(pipes[i - 1][0], 0);
	close(pipes[i - 1][0]);
	dup2(pipes[i][1], 1);
	close(pipes[i][1]);
	close(pipes[i][0]);
	exec_path(input);
	// execve("/bin/ps", args2, envp);
}

void	parent_close_fd(int **pipes, int i)
{
	if (i == 0)
		close(pipes[i][1]);
	else if (i == data->pipe_number)
		close(pipes[i - 1][0]);
	else
	{
		close(pipes[i - 1][0]);
		close(pipes[i][1]);
	}
}

int	exec_pipes(char *input)
{
	int	i;
	int	process;
	int	**pipes;
	int	status;

	pipes = get_pipes();
	i = -1;
	while (++i <= data->pipe_number)
	{
		process = fork();
		if (process == 0)
		{
			if ((i == 0) || (i == data->pipe_number))
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
