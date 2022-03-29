/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_tokenize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatan <jatan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 11:36:13 by jatan             #+#    #+#             */
/*   Updated: 2022/03/29 11:36:47 by jatan            ###   ########.fr       */
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
