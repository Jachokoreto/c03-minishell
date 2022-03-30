/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mypipe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 16:11:43 by leu-lee           #+#    #+#             */
/*   Updated: 2022/03/24 16:13:17 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>

int	**get_pipes(int nopipes)
{
	int	**pipes;
	int	i;

	pipes = malloc(sizeof(int *) * nopipes);
	i = 0;
	while (i < nopipes)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		pipe(pipes[i]);
		i++;
	}
	return (pipes);
}

int	main(void)
{
	int	fd_out;
	int	i;
	int	process;
	int	**pipes;
	int	nopipes;
	int	fd_in;
	char *args[] = {"/bin/cat", NULL};
	char *args1[] = {"/bin/ls", NULL};
	char *args2[] = {"/bin/ps", NULL};
	int status;

	nopipes = 10;
	pipes = get_pipes(nopipes);
	fd_out = open("outfile",  O_CREAT |O_WRONLY | O_APPEND, 0644);
	i = 0;
	while (i < (nopipes + 1))
	{
		process = fork();
		if (process == 0)
		{
			if (i == 0)
			{
				// first child
				fd_in = open("infile", O_RDONLY, 0777);
				dup2(fd_in, 0); //stdinput with inputfile
				close(fd_in); 
				dup2(pipes[i][1], 1); //stdout to stdoutput pipe
				close(pipes[i][1]);
				close(pipes[i][0]);
				execve("/bin/ls", args1, NULL);
			}
			else if (i == nopipes)
			{
				// last child
				dup2(pipes[i - 1][0], 0);
				close(pipes[i - 1][0]);
				close(pipes[i - 1][1]);
				dup2(fd_out, 1);
				close(fd_out);
				execve("/bin/cat", args, NULL);
			}
			else
			{
				// other children
				dup2(pipes[i - 1][0], 0); //stdinput to stdinput pipe
				close(pipes[i - 1][0]);
				//1 pipe is used now
				dup2(pipes[i][1], 1); //
				close(pipes[i][1]);
				close(pipes[i][0]);
				execve("/bin/ps", args2, NULL);
			}
			
		}
		if (i == 0)
		{
			close(pipes[i][1]);
		}
		else if (i == nopipes)
		{
			close(pipes[i - 1][0]);			
		}
		else
		{
			close(pipes[i - 1][0]);
			close(pipes[i][1]);
		}
		while(waitpid(-1, &status, 0) > 0)
			;
		i++;
	}
	return (0);
}