/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_decide_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 11:36:13 by jatan             #+#    #+#             */
/*   Updated: 2022/05/01 12:44:56 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Adds a new token to the t_token linked list
 * The type is determined in the if else statements in the decide token func.
 * The value itself is determined
 */

static t_token	*add_new_token(t_data *data, char *str, enum e_Type type)
{
	t_token	*token;
	char	*tmp;

	tmp = process_buffer(str, data->envp);
	if (tmp == NULL)
		return (NULL);
	token = ft_calloc(1, sizeof(t_token));
	token->type = type;
	token->value = tmp;
	ft_lstadd_back(&data->tokens, ft_lstnew(token));
	return (token);
}

/**
 * enumeration of redirection types
 */

static enum e_Type	set_file_type(char *value)
{
	if (utl_strncmp(value, "<<") == 0)
		return (delim);
	else if (utl_strncmp(value, "<") == 0)
		return (infile);
	else if (utl_strncmp(value, ">") == 0)
		return (outfile1);
	else
		return (outfile2);
}

/**
 * Decide tokens read the string and determine its token_type
 * It goes into add_new_token which assigns the type and value on its
 * respective linked list node.
 */

int	decide_token(char *str, t_data *data)
{
	static t_token	*p_token;
	enum e_Type		type;

	if (data->tokens == NULL)
		p_token = NULL;
	if (utl_strncmp(str, "|") == 0)
	{
		if (p_token == NULL || p_token->type == redir)
			return (1);
		type = pip;
	}
	else if (utl_strncmp(str, ">>") == 0 || utl_strncmp(str, "<<") == 0
		|| utl_strncmp(str, ">") == 0 || utl_strncmp(str, "<") == 0)
	{
		if (p_token == NULL || p_token->type == redir)
			return (1);
		type = redir;
	}
	else if (p_token != NULL && p_token->type == redir)
		type = set_file_type(p_token->value);
	else
		type = arg;
	p_token = add_new_token(data, str, type);
	return (0);
}
