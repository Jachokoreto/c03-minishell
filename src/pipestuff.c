#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

pid_t	call(char *argv[])
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		char* envp[] = { NULL };
		execve(argv[0], argv, envp);
		perror("could not execve");
		exit (1);
	}
	else
		return (pid);
}

int	main(void)
{
	printf("Hello from parent process~~!\n");
	char* argv[] = { "./sub", NULL };
	pid_t pid = call(argv);
	printf("New process got pid: %d\n", pid);
	return 0;
	
}