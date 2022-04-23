/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_decide_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatan <jatan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 11:36:13 by jatan             #+#    #+#             */
/*   Updated: 2022/04/23 14:45:27 by jatan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Adds a new token to the t_token linked list
 * The type is determined in the if else statements in the decide token func.
 * The value itself is determined
 */

t_token	*add_new_token(t_data *g_data, char *str, enum e_Type type)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	token->type = type;
	token->value = process_buffer(str, g_data->envp);
	ft_lstadd_back(&g_data->tokens, ft_lstnew(token));
	return (token);
}

/**
 * Decide tokens read the string and determine its token_type
 * It goes into add_new_token which assigns the type and value on its
 * respective linked list node.
 */

void	decide_token(char *str, t_data *g_data)
{
	static t_token	*p_token;
	enum e_Type		type;

	if (g_data->tokens == NULL)
		p_token = NULL;
	if (utl_strncmp(str, "|") == 0)
		type = pip;
	else if (utl_strncmp(str, ">>") == 0 || utl_strncmp(str, "<<") == 0
		|| utl_strncmp(str, ">") == 0 || utl_strncmp(str, "<") == 0)
		type = redir;
	else if (p_token != NULL && p_token->type == redir)
	{
		if (utl_strncmp(p_token->value, "<<") == 0)
			type = delim;
		else if (utl_strncmp(p_token->value, "<") == 0)
			type = infile;
		else if (utl_strncmp(p_token->value, ">") == 0)
			type = outfile1;
		else
			type = outfile2;
	}
	else
		type = arg;
	p_token = add_new_token(g_data, str, type);
}
