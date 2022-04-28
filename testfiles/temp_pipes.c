/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 16:54:56 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/28 11:38:32 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	**get_pipes(void)
{
	int	**pipes;
	int	i;

	pipes = ft_calloc(data->pipe_number, sizeof(int *));
	i = 0;
	while (i < data->pipe_number)
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
	int	infile = 0; // temp again
	if (i == 0)
	{
		printf("firstchild\n");
		if (infile > 0)
		{
			fd_in = open("infile", O_RDONLY, 0777); // maybe initialize beforehand
			dup2(fd_in, 0);
			close(fd_in);
		}
		if (data->pipe_number > 0)
		{
			dup2(pipes[i][1], 1);
			close(pipes[i][1]);
			close(pipes[i][0]);
		}
		exe_path(input);
	}
	else if (i == data->pipe_number)
	{
		printf("lastchild\n");
		// fix when there is only 1 pipe
		fd_out = open("outfile", O_CREAT | O_WRONLY| O_APPEND, 0644);
		// if (i == data->pipe_number)
		// {
			// printf("if\n");
		dup2(pipes[i][0], 0);
		close(pipes[i][0]);
		close(pipes[i][1]);
		// }
		// else
		// {
		// 	printf("else\n");
		// 	dup2(pipes[i - 1][0], 0);
		// 	close(pipes[i - 1][0]);
		// 	close(pipes[i - 1][1]);
		// }
		dup2(fd_out, 1);
		close(fd_out);
		exe_path(input);
	}
}

void	middle_child(int **pipes, int i, char *input)
{
	printf("middlechild\n");
	dup2(pipes[i - 1][0], 0);
	close(pipes[i - 1][0]);
	dup2(pipes[i][1], 1);
	close(pipes[i][1]);
	dup2(redir_in, 0);
	exe_path(input);
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

int	exe_pipe_cmds(char *input)
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
