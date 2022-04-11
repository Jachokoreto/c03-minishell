#include "minishell.h"

int	ft_fork(void)
{
	int	process;

	process = fork();
	if (process == -1)
	{
		perror("fork failed");
		exit(errno);
	}
	return (process);
}

void	ft_kill(pid_t pid, int sig)
{
	if (kill(pid, sig) == -1)
	{
		perror("Kill failed");
		exit(errno);
	}
}

void	ft_pipe(int pipefd[2])
{
	if (pipes(pipefd) == -1)
	{
		perror("Pipe failed\n");
		exit(errno);
	}
}
