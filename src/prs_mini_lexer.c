/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_mini_lexer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:16:57 by jatan             #+#    #+#             */
/*   Updated: 2022/05/06 11:04:02 by leu-lee          ###   ########.fr       */
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

static char	*get_string_into_buffer(char **line)
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

static int	check_token(t_data *data)
{
	t_list	*token_lst;
	t_token	*token;

	token_lst = data->tokens;
	while (token_lst)
	{
		token = token_lst->content;
		if ((token->type == redir || token->type == pip)
			&& token_lst->next == NULL)
			return (1);
		token_lst = token_lst->next;
	}
	return (0);
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
				return (utl_error("Syntax error: unexpected quotes\n", 1));
			if (decide_token(buffer, data) == 1)
			{
				free(buffer);
				return (utl_error("Syntax error: unexpected token\n", 1));
			}
		}
	}
	if (check_token(data) == 1)
		return (utl_error("Syntax error: unexpected token\n", 1));
	return (0);
}
