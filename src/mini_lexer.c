/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatan <jatan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:16:57 by jatan             #+#    #+#             */
/*   Updated: 2022/03/23 16:25:20 by jatan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*add_new_token(char *arg, enum e_Type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->type = type;
	token->value = arg;
	ft_lstadd_back(data->tokens, ft_lstnew(token));
	return (token);
}



t_list	*mini_lex(char *line)
{
	int		i;
	int		start_idx;
	char	*buffer;
	t_token	*prev_token;

	prev_token = NULL;
	i = 0;
	while (line[i])
	{
		start_idx = i;
		while (line[i] == ' ')
			i++;
		while (ft_isalnum(line[i]) == 1)
			i++;
		if (line[i] == '<' || line[i] == '>' || line[i] == '|')
			i++;
		if (line[i] == '<' || line[i] == '>')
			i++;
		buffer = ft_substr(line, start_idx, i - start_idx);
		if (buffer[0] == '|')
			prev_token = add_new_token(buffer, pip);
		else if (ft_strncmp(buffer, ">>", 2) == 1
			|| buffer[0] == '>' || buffer[0] == '<')
			prev_token = add_new_token(buffer, redir);
		else if (prev_token == NULL || (prev_token && prev_token->type == pip))
			prev_token = add_new_token(buffer, cmd);
		else if (prev_token->type == cmd)
			prev_token = add_new_token(buffer, arg);
		else if (prev_token->type == redir)
			prev_token = add_new_token(buffer, file);
	}
}