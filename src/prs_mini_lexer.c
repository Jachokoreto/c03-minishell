/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_mini_lexer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:16:57 by jatan             #+#    #+#             */
/*   Updated: 2022/04/06 17:20:47 by leu-lee          ###   ########.fr       */
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
		// redir and pipes handled here
		if (*index == '<' || *index == '>' || *index == '|')
		{
			// 1. if the index is still line
			// 2. move the pointer address of index.
			// 3. if the character of index before that is the same index 
			//		(already ++index so yea)
			// 4. if the index IS NOT a pipe then it breaks.
			if (index == *line && *(++index)
				&& *index == *(index - 1) && *(index - 1) != '|')
				index++;
			break ;
		}
		// double and single quotes handled here
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
		// skip spaces of the line.
		while (*line == ' ')
			line++;
		// takes string to buffer.
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
