/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_mini_lexer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatan <jatan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:16:57 by jatan             #+#    #+#             */
/*   Updated: 2022/03/30 10:53:44 by jatan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_string_into_buffer(char **line)
{
	char	*index;
	char	*buffer;

	index = *line;
	while (*index && *index != ' ')
	{
		if (*index == '<' || *index == '>' || *index == '|')
		{
			if (index == *line && *(++index)
				&& *index == *(index - 1) && *(index - 1) != '|')
				index++;
			break ;
		}
		if (*index == '\"' || *index == '\'')
		{
			index = ft_strchr(index + 1, *index);
			if (index == NULL)
				return (NULL);
		}
		index++;
	}
	buffer = ft_substr(*line, 0, index - *line);
	*line = index;
	return (buffer);
}

// this wont skip to over to after variable
void	mini_lexer(char *line)
{
	int		i;
	char	*buffer;

	i = 0;
	g_data->tokens = NULL;
	buffer = NULL;
	while (*line)
	{
		while (*line == ' ')
			line++;
		buffer = get_string_into_buffer(&line);
		if (buffer == NULL)
		{
			perror("Invalid");
			break ;
		}
		buffer = process_buffer(buffer);
		decide_token(buffer);
		free(buffer);
	}
}
