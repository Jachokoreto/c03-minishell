/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:36:52 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/07 17:51:11 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc(char *delim)
{
	char		*str;
	char		*temp;
	char		*line;
	// char 		*argv[] = {"/bin/cat", NULL};
	int			pipefd[2];
	int			process;
	int			fd_temp;

	str = ft_calloc(1, sizeof(char));
	if (delim == NULL)
		return ;
	// heredocsignals();
	pipe(pipefd);
	while (1)
	{
		line = readline("heredoc > ");
		if (line == NULL)
			continue ;
		if (!str)
			str = ft_strdup(line);
		else
		{
			if (strncmp(line, ft_strjoin(delim, "\n"), ft_strlen(line)) == 0)
			{
				process = fork();
				if (process == 0)
				{
					printf("str:\n %s\n", str);
					fd_temp = open( "heredocfile", O_WRONLY | O_CREAT | O_TRUNC,
							0666);
					dup2(fd_temp, 0);
					ft_putstr_fd(str, 0);
					close(fd_temp);
					// fd_temp = open( "tempfile", O_RDONLY);
					// dup2(fd_temp, 1);
					//execve("/bin/cat", argv, NULL);
				}
				break ;
			}
			temp = ft_strdup(line);
			temp = ft_strjoin(str, line);
			str = ft_strdup(temp);
			str = ft_strjoin(str, "\n");
			free(temp);
		}
	}
	// printf("%s", str);
	return ;
}
