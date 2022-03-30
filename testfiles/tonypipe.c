# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main ()
{
	int fd[2];
	int process;
	int out_fd;
	char *args[] = {"/bin/cat", NULL};
	char *args1[] = {"/bin/ls", NULL};
	char *envp[] = {NULL};


	out_fd = open("outfile", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	pipe(fd);
	int i = 0;
	while (i < 3)
	{
		process = fork();
		if (process == 0)
		{
			if (i == 0)
			{
				// Child process 1 runs
				int in_fd;
				in_fd = open("infile2", O_RDONLY, 0644);
				dup2(in_fd, 0); //  duplicate stdinput with stdinput to make it point to the infile
				close (in_fd); // closing stdinput of infile
				dup2(fd[1], 1); //duplicate stdinput with output of the pipe
				close(fd[1]); // closing stdinput of the pipe
				close(fd[0]); // closing stdoutput of the pipe
				execve("/bin/ls", args1, envp);
			}
			else if (i == 1)
			{
				// Child process 2 runs
				dup2(fd[0], 0); // duplicate stdinput with stdinput of pipe
				close(fd[0]); // close stdinput of pipe
				dup2(out_fd, 1); // duplicate stdoutput with stdoutput of outfile
				close (out_fd); // closing stdoutput of outfile.
				execve("/bin/cat", args, envp);
			}
		}
		if (i == 0)
		{
			close(fd[1]); // closing std output of the pipe
		}
		else if (i == 1)
		{
			close(fd[0]); // closing std input of the pipe
		}




		i++;
	}
	//printf("In fd is %i\n", in_fd);
	return (0);
}