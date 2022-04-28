/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_mini_lexer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:16:57 by jatan             #+#    #+#             */
/*   Updated: 2022/04/28 11:38:32 by leu-lee          ###   ########.fr       */
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
int	mini_lexer(char *line, t_data *data)
{
	char	*buffer;

	data->tokens = NULL;
	buffer = NULL;
	while (*line)
	{
		while (*line == ' ')
			line++;
		if (*line)
		{
			buffer = get_string_into_buffer(&line);
			if (buffer == NULL)
			{
				g_exit = 1;
				ft_putstr_fd("Syntax error : unclosed quotes\n", 2);
				return (1);
			}
			decide_token(buffer, data);
		}
	}
	return (0);
}
