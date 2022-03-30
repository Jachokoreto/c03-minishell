# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>
#define BUFFER_SIZE 42

int	main(void)
{
	int	fd_in;
	int	fd_out;
	int	i;
	int	process;
	int	status;
	char *argv[] = {"/bin/cat", NULL};

	fd_out = open("outfile", O_WRONLY | O_CREAT | O_APPEND, 0777);
	process = fork();
	if (process == 0)
	{
		fd_in = open("infile", O_RDWR, 0777);
		dup2(fd_in, 0);
		close(fd_in);
		dup2(fd_out, 1);
		close(fd_out);
		execve("/bin/cat", argv, NULL);
	}
}
