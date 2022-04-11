/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:36:52 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/10 10:09:51 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc(char *delim)
{
	char		*str;
	char		*temp;
	char		*line;
	int			saved_stdin;
	int			fd_temp;

	str = ft_calloc(1, sizeof(char));
	if (delim == NULL)
		return (0);
	// heredocsignals();
	while (1)
	{
		line = readline("heredoc > ");
		if (strncmp(line, delim, ft_strlen(line)) == 0)
		{
			// printf("%s", str);
			saved_stdin = dup(0);
			fd_temp = ft_open("heredocfile", O_WRONLY | O_CREAT | O_TRUNC,
					0666);
			ft_putstr_fd(str, fd_temp);
			//close(fd_temp);
			// dup2(saved_stdin, 0);
			// close(saved_stdin);
			break ;
		}
		temp = ft_strjoin(str, line);
		str = ft_strjoin(temp, "\n");
		free(temp);
	}
	free(str);
	return (fd_temp);
}
