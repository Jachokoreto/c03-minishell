/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatan <jatan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:16:57 by jatan             #+#    #+#             */
/*   Updated: 2022/03/28 18:48:56 by jatan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*add_new_token(char *str, enum e_Type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->type = type;
	token->value = ft_strdup(str);
	ft_lstadd_back(&g_data->tokens, ft_lstnew(token));
	return (token);
}

void	decide_token_type(char *str)
{
	static t_token	*prev_token;

	if (g_data->tokens == NULL)
		prev_token = NULL;
	if (str[0] == '|')
		prev_token = add_new_token(str, pip);
	else if (ft_strncmp(str, ">>", 2) == 1
		|| str[0] == '>' || str[0] == '<')
		prev_token = add_new_token(str, redir);
	else if (prev_token == NULL || (prev_token && prev_token->type == pip))
		prev_token = add_new_token(str, cmd);
	else if (prev_token->type == redir)
		prev_token = add_new_token(str, file);
	else
		prev_token = add_new_token(str, arg);
}


char	*expand_env_var(char *buf)
{
	char	*tmp[4];

	while (buf)
	{
		tmp[3] = ft_strchr(buf, '$');
		if (tmp[3] == NULL || tmp[3])
			break ;
		tmp[1] = ft_substr(buf, 0, tmp[3] - buf);
		buf = tmp[3] + 1;
		while (ft_isalnum(*buf) == 1 || *buf == '_')
			buf++;
		tmp[0] = ft_substr(tmp[3], 0, buf - tmp[3]);
		tmp[2] = ft_strdup(buf);
		free(buf);
		buf = ft_strjoin(tmp[1], mini_getenv(tmp[0]));
		free(tmp[0]);
		tmp[0] = buf;
		buf = ft_strjoin(buf, tmp[2]);
		free(tmp[0]);
		free(tmp[1]);
		free(tmp[2]);
	}
	return (buf);
}

char	*get_string_into_buffer(char **line)
{
	char	*index;
	char	*buffer;

	index = *line;
	while (*index && *index != ' ')
	{
		if (*index == '<' || *index == '>' || *index == '|')
		{
			if (index == *line
				&& *(++index) && *index == *(index - 1) && *(index - 1) != '|')
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

// char	*process_buffer(char *buffer)
// {
// 	int	quoted;

// 	quoted = 0;

// }

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
		decide_token_type(buffer);
		free(buffer);
	}
}
