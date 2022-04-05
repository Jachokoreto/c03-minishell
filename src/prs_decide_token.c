/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_decide_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatan <jatan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 11:36:13 by jatan             #+#    #+#             */
/*   Updated: 2022/04/04 19:33:43 by jatan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*add_new_token(char *str, enum e_Type type)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	token->type = type;
	token->value = ft_strdup(str);
	ft_lstadd_back(&g_data->tokens, ft_lstnew(token));
	return (token);
}

void	decide_token(char *str)
{
	static t_token	*p_token;

	if (g_data->tokens == NULL)
		p_token = NULL;
	if (str[0] == '|')
		p_token = add_new_token(str, pip);
	else if (ft_strncmp(str, ">>", 2) == 1 || str[0] == '>' || str[0] == '<')
		p_token = add_new_token(str, redir);
	else if (p_token == NULL || (p_token && p_token->type == pip))
		p_token = add_new_token(str, arg);
	else if (p_token->type == redir && ft_strncmp(p_token->value, "<<", 2) == 0)
		p_token = add_new_token(str, delim);
	else if (p_token->type == redir && ft_strncmp(p_token->value, "<", 1) == 0)
		p_token = add_new_token(str, infile);
	else if (p_token->type == redir && (ft_strncmp(p_token->value, ">", 1) == 0
			|| ft_strncmp(p_token->value, ">>", 2) == 0))
		p_token = add_new_token(str, outfile);
	else
		p_token = add_new_token(str, arg);
}
