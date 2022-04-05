/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatan <jatan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 10:34:39 by jatan             #+#    #+#             */
/*   Updated: 2022/04/04 19:28:43 by jatan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	parser(char *line)
{
	t_list		*tmp;
	t_list		*tmp2;
	t_token		*tmp_token;
	t_cmd_grp	*tmp_cmd;
	int			i;

	mini_lexer(line);
	tmp = g_data->tokens;
	while (tmp)
	{
		tmp_token = tmp->content;
		printf("%d, |%s|\n", tmp_token->type, tmp_token->value);
		tmp = tmp->next;
	}
	mini_yacc();
	tmp = g_data->cmd_grps;
	printf("cmd grp size: %d\n", ft_lstsize(tmp));
	while (tmp)
	{
		tmp_cmd = (t_cmd_grp *)tmp->content;
		i = -1;
		while (tmp_cmd->args[++i])
			printf("args %d : %s\n", i, tmp_cmd->args[i]);
		tmp2 = tmp_cmd->retokens;
		while (tmp2)
		{
			tmp_token = tmp2->content;
			printf("%d, |%s|\n", tmp_token->type, tmp_token->value);
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
		printf("----next cmd grps----\n");
	}
}
