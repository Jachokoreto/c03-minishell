/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_decide_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 11:36:13 by jatan             #+#    #+#             */
/*   Updated: 2022/04/14 14:51:15 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*add_new_token(char *str, enum e_Type type)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	token->type = type;
	token->value = process_buffer(str);
	ft_lstadd_back(&g_data->tokens, ft_lstnew(token));
	return (token);
}

void	decide_token(char *str)
{
	static t_token	*p_token;
	int				l;

	l = ft_strlen(str);
	if (g_data->tokens == NULL)
		p_token = NULL;
	if (ft_strncmp(str, "|", l) == 0)
		p_token = add_new_token(str, pip);
	else if (ft_strncmp(str, ">>", l) == 0 || ft_strncmp(str, "<<", l) == 0
		|| ft_strncmp(str, ">", l) == 0 || ft_strncmp(str, "<", l) == 0)
		p_token = add_new_token(str, redir);
	else if (p_token != NULL && p_token->type == redir)
	{
		if (ft_strncmp(p_token->value, "<<", l) == 0)
			p_token = add_new_token(str, delim);
		else if (ft_strncmp(p_token->value, "<", l) == 0)
			p_token = add_new_token(str, infile);
		else if (ft_strncmp(p_token->value, ">", l) == 0)
			p_token = add_new_token(str, outfile1);
		else if (ft_strncmp(p_token->value, ">>", l) == 0)
			p_token = add_new_token(str, outfile2);
	}
	else
		p_token = add_new_token(str, arg);
}
