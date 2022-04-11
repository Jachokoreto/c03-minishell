/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_mini_lexer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:16:57 by jatan             #+#    #+#             */
/*   Updated: 2022/04/11 22:05:29 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 1. if the index is still line
 * 2. move the pointer address of index.
 * 3. if the character of index before that is the same index 
 *		(already ++index so yea)
 * 4. if the index IS NOT a pipe then it breaks.
 */
char	*get_string_into_buffer(char **line)
{
	char	*index;
	char	*buffer;

	index = *line;
	while (*index && *index != ' ')
	{
		if (*index == '<' || *index == '>' || *index == '|')
		{
			while (*index == **line)
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

/**
 * Iterate through the input line to identify commands and argument in order to 
 * categorize each token for the yacc.
 * the spaces will be ignored until reaching an argument before passing it into
 * "get_string_into_buffer". After getting the string, the string will be 
 * tokenized.
 */
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
		decide_token(buffer);
		free(buffer);
	}
}
