#include "minishell.h"
#include <signal.h>
#include <errno.h>

int	ft_open(char *filename, int oflag, int mode)
{
	int	fd;

	fd = open(filename, oflag, mode);
	if (fd == - 1)
	{
		perror("open failed");
		exit(errno);
	}
	return (fd);
}

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

int	ft_read(int fd, void *buf, size_t count)
{
	int	ret;

	ret = read(fd, buf, count);
	if (ret == -1)
	{
		perror("read failed");
		exit(errno);
	}
	return (ret);
}

void	ft_close(int fd)
{
	if (close(fd)== -1)
	{
		perror("close failed");
		exit(errno);
	}
}

void	ft_dup2(int oldfd, int newfd)
{

	if (dup2(oldfd, newfd) == -1)
	{
		perror("dup2 failed");
		exit(errno);
	}
}

void ft_execve(const char *pathname, char *const argv[], char *const envp[])
{
	if (execve(pathname, argv, envp) == -1)
	{
		perror("execve failed");
		exit(errno);
	}
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
