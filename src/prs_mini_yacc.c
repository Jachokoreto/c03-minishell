/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_mini_yacc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:12:55 by jatan             #+#    #+#             */
/*   Updated: 2022/04/28 11:38:32 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * The count arguments count how many arguments in each command groups.
 * If it finds a pipe, it immediately breaks as that would mean that the
 * arguments would belong in another command group.
 */

int	count_args(t_list *token_lst)
{
	t_token	*token;
	int		count;

	count = 0;
	while (token_lst)
	{
		token = (t_token *)token_lst->content;
		if (token->type == pip)
			break ;
		if (token->type == arg)
			count++;
		token_lst = token_lst->next;
	}
	return (count);
}

/**
 * The argument values are determined through lexer and this function will 
 * duplicate each of the token value into its respective value.
 */
void	set_arg_value(char ***value, int c, enum e_Type type, t_list *tokens)
{
	t_token	*token;
	int		i;

	*value = ft_calloc(c + 1, sizeof(char *));
	i = 0;
	while (i < c)
	{
		token = (t_token *)tokens->content;
		if (token->type == type)
			(*value)[i++] = ft_strdup(token->value);
		tokens = tokens->next;
	}
	(*value)[c] = NULL;
}

/**
 * Mini_yacc inserts the processed tokens into its respective groups.
 * It counts how many arguments are there in the command group using count_args
 * Once the number of arguments are counted, the arguments will be set using the
 * set_arg_value function. The redirection tokens are then innitialized in each
 * command group.
 */

void	mini_yacc(t_data *data)
{
	t_list		*token_lst;
	t_token		*token;
	t_cmd_grp	*cmd_grp;
	int			count;

	token_lst = data->tokens;
	while (token_lst)
	{
		cmd_grp = ft_calloc(1, sizeof(t_cmd_grp));
		count = count_args(token_lst);
		set_arg_value(&cmd_grp->args, count, arg, token_lst);
		while (token_lst->next)
		{
			token_lst = token_lst->next;
			token = (t_token *)token_lst->content;
			if (token->type == pip)
				break ;
			else if (token->type != arg && token->type != redir)
				ft_lstadd_back(&cmd_grp->retokens, ft_lstnew(token));
		}
		ft_lstadd_back(&data->cmd_grps, ft_lstnew(cmd_grp));
		token_lst = token_lst->next;
	}
}
