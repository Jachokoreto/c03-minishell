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
	int	fd_out2;
	int	fd_out;
	int	i;
	int ret;
	char	buffer[256];
	char	*line;
	char	*str;
	char	*temp;
	int	process[2];
	int	status;
	char *argv[] = {"/bin/cat", NULL};

	fd_out = open("outfile1", O_WRONLY | O_CREAT | O_APPEND, 0777);
	fd_out2 = open("outfile2", O_WRONLY | O_CREAT | O_APPEND, 0777);
	process[0] = fork();
	if (process[0] == 0)
	{
		fd_in = open("infile", O_RDONLY, 0777);
		dup2(fd_in, 0);
		if (!str)
		{
			str = ft_calloc(sizeof(char));
			str[0] = 0;			
		}
		ret = read(fd_in, buffer, 256);
		buffer[ret] = '\0';
		close(fd_in);
		// temp = ft_strjoin(str, buffer);
		// str = temp;
		// free(temp);

		dup2(fd_out, 1);
		close(fd_out);

		// dup2(fd_out2 , 1);
		// close(fd_out2);
		process[1] = fork();
		if (process[1] == 0) 
			execve("/bin/cat", argv, NULL);

	}
}
