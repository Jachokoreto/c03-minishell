/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatan <jatan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:36:52 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/29 18:59:51 by jatan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc(char *delim)
{
	char		*str;
	char		*line;
	int			fd_temp;

	fd_temp = ft_open("heredocfile", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	while (1)
	{
		line = readline("heredoc > ");
		if (line == NULL)
			break ;
		if (utl_strncmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		str = ft_strjoin(line, "\n");
		ft_putstr_fd(str, fd_temp);
		free(str);
		free(line);
	}
	close(fd_temp);
	fd_temp = ft_open("heredocfile", O_RDONLY, 0666);
	return (fd_temp);
}
