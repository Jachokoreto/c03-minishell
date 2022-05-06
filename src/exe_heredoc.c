/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:36:52 by leu-lee           #+#    #+#             */
/*   Updated: 2022/05/05 21:42:22 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Heredoc opens a temp file.
 * This temp filed will be read from readline with its heredoc prompt.
 * Once the delim is found, the heredoc will break and return as a fd_in.
 */

// char	*heredoc(char *delim)
// {
// 	char		*str;
// 	char		*line;
// 	int			fd_temp;

// 	fd_temp = ft_open(".heredocfile", O_WRONLY | O_CREAT | O_TRUNC, 0666);
// 	while (1)
// 	{
// 		line = readline("heredoc > ");
// 		if (line == NULL)
// 			break ;
// 		if (utl_strncmp(line, delim) == 0)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		str = ft_strjoin(line, "\n");
// 		ft_putstr_fd(str, fd_temp);
// 		free(str);
// 		free(line);
// 	}
// 	close(fd_temp);
// 	// fd_temp = ft_open(".heredocfile", O_RDONLY, 0666);
// 	return (".heredocfile");
// }
