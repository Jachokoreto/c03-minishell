/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:36:52 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/11 18:57:37 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc(char *delim)
{
	char		*str;
	char		*line;
	int			fd_temp;

	// if (delim == NULL)
	// 	return (0);
	// heredocsignals();
	fd_temp = ft_open("heredocfile", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	while (1)
	{
		line = readline("heredoc > ");
		if (utl_strncmp(line, delim) == 0)
			break ;
		str = ft_strjoin(line, "\n");
		ft_putstr_fd(str, fd_temp);
		free(str);
	}
	close(fd_temp);
	fd_temp = ft_open("heredocfile", O_RDONLY, 0666);
	return (fd_temp);
}
