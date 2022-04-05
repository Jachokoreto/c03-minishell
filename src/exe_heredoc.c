/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:36:52 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/05 15:59:34 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc(char *delim)
{
	char		*str;
	char		*temp;
	char		*line;
	int			process;

	str = malloc(sizeof(char));
	if (delim == NULL)
		return ;
	// heredocsignals();
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
				break ;
			temp = ft_strdup(line);
			temp = ft_strjoin(str, line);
			str = ft_strdup(temp);
			str = ft_strjoin(str, "\n");
			free(temp);
		}
		if ((strncmp(line, ft_strjoin(delim, "\n"), ft_strlen(line)) == 0))
		{
			process = fork ();
			if (process == 0)
				exe_path(str);
			break ;
		}
	}
	printf("%s", str);
	return ;
}
