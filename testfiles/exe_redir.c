#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

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
	fd_out = open("outfile", O_WRONLY | O_CREAT | O_APPEND, 0777);
	process = fork();
	i = -1;
	if (process == 0)
	{
		while (++i < redir_in)
		{
			if (i == 0)
			{	
				fd_in = open("infile", O_RDWR, 0777);
				if (fd_in == -1)
				{
					printf("Error\n");
					return (1);
				}
			}
			if (i == 1)
				fd_in = open("infile1", O_RDWR, 0777);
			dup2(fd_in, 0);
			close(fd_in);
		}		
		i = -1;
		while (++i < redir_out)
		{
			if (i == 0)
				fd_out = open("outfile", O_WRONLY | O_CREAT | O_APPEND, 0777);
			if (i == 1)
				fd_out = open("outfile2", O_WRONLY | O_CREAT | O_APPEND, 0777);
			dup2(fd_out, 1);
			close(fd_out);
		}
		execve("/bin/cat", argv, NULL);
	}
	return (0);
}
