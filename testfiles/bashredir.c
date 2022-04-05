#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

char	**get_infiles()
{
	char	**infiles;

	infiles = malloc(sizeof(char *) * 3);
	infiles[0] = "infile";
	infiles[1] = "infile1";
	return (infiles);
}

char	**get_outfiles()
{
	char	**outfiles;

	outfiles = malloc(sizeof(char *) * 3);
	outfiles[0] = "0outfile";
	outfiles[1] = "1outfile2";
	return (outfiles);
}

int	ft_open(char *filename, int oflag, int mode)
{
	int	fd;

	fd = open(filename, oflag, mode);
	if (fd == - 1)
	{
		printf("Error\n");
		exit(1);
	}
	return (fd);
}

void	output_redir(int redir_out)
{
	int	i;
	int	fd_out;
	char	**outfiles;

	outfiles = get_outfiles();
	i = -1;
	while (++i < redir_out)
	{ // might need to change to linked list
		if (outfiles[i][0] == '0')
		{
			if (i == 0)
				fd_out = ft_open( &outfiles[0][1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if (i == 1)
				fd_out = ft_open( &outfiles[1][1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		}
		else
		{
			if (i == 0)
				fd_out = ft_open( &outfiles[0][1], O_WRONLY | O_CREAT | O_APPEND, 0777);
			if (i == 1)
				fd_out = ft_open( &outfiles[1][1], O_WRONLY | O_CREAT | O_APPEND, 0777);
		}
		dup2(fd_out, 1);
		close(fd_out);
	}
}

void	input_redir(int redir_in)
{
	int	i;
	int	fd_in;
	char **infiles;

	infiles = get_infiles();
	i = -1;
	while (++i < redir_in)
	{
		if (i == 0)
			fd_in = ft_open( infiles[0], O_RDWR, 0777);
		if (i == 1)
			fd_in = ft_open( infiles[1], O_RDWR, 0777);
		dup2(fd_in, 0);
		close(fd_in);
	}
}

int	main(void)
{
	int	fd_in;
	int	fd_out;
	int	i;
	int	process;
	int	redir_in;
	int	redir_out;
	char *argv[] = {"/bin/cat", NULL};

	redir_in = 2;
	redir_out = 2;
	// fork is just to test if it works or not
	process = fork();
	if (process == 0)
	{
		input_redir(redir_in);
		output_redir(redir_out);
		execve("/bin/cat", argv, NULL);
	}
	return (0);
}
