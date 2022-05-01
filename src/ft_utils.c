/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 09:43:38 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/23 16:46:42 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (pipe(pipefd) == -1)
	{
		perror("Pipe failed\n");
		exit(errno);
	}
}

void	ft_tcgetattr(int fd, struct termios *termios_p)
{
	if (tcgetattr(fd, termios_p) == -1)
	{
		perror("Tcgetattr failed\n");
		exit(errno);
	}
}

void	ft_tcsetattr(int fd, int optional_actions,
	const struct termios *termios_p)
{
	if (tcsetattr(fd, optional_actions, termios_p) == -1)
	{
		perror("Tcsetattr failed\n");
		exit(errno);
	}
}
