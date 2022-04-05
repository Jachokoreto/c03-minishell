/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_mini_yacc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatan <jatan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:12:55 by jatan             #+#    #+#             */
/*   Updated: 2022/04/04 19:23:15 by jatan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*count_tokens(t_list *token_lst)
{
	t_token	*token;
	int		*count;

	count = ft_calloc(4, sizeof(int));
	while (token_lst)
	{
		token = (t_token *)token_lst->content;
		if (token->type == pip)
			break ;
		if (token->type == arg)
			count[0]++;
		else if (token->type == redir && ft_strlen(token->value) == 1)
			count[(*token->value == '<') * 1 + (*token->value == '>') * 2]++;
		else if (token->type == redir && ft_strncmp(token->value, ">>", 2) == 0)
			count[2]++;
		else if (token->type == redir && ft_strncmp(token->value, "<<", 2) == 0)
			count[3]++;
		token_lst = token_lst->next;
	}
	return (count);
}

//go through token
void	set_cmd_value(char ***value, int c, enum e_Type type, t_list *tokens)
{
	t_token	*token;
	t_token	*p_token;
	int		i;

	*value = ft_calloc(c + 1, sizeof(char *));
	i = 0;
	while (i < c)
	{
		token = (t_token *)tokens->content;
		if (token->type == type && type != outfile)
			(*value)[i++] = token->value;
		p_token = token;
		tokens = tokens->next;
	}
	(*value)[c] = NULL;
}

// take token and organize into cmd_grp
void	mini_yacc(void)
{
	t_list		*token_lst;
	t_token		*token;
	t_cmd_grp	*cmd_grp;
	int			*count;

	token_lst = g_data->tokens;
	while (token_lst)
	{
		cmd_grp = ft_calloc(1, sizeof(t_cmd_grp));
		count = count_tokens(token_lst);
		printf("ARGS\n");
		set_cmd_value(&cmd_grp->args, count[0], arg, token_lst);
		while (token_lst->next)
		{
			token_lst = token_lst->next;
			token = (t_token *)token_lst->content;
			if (token->type == pip)
				break ;
			else if (token->type != arg)
				ft_lstadd_back(&cmd_grp->retokens, ft_lstnew(token));
		}
		ft_lstadd_back(&g_data->cmd_grps, ft_lstnew(cmd_grp));
		token_lst = token_lst->next;
		printf("asdf\n\n");
	}
	free(count);
}
