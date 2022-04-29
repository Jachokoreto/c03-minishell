/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatan <jatan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 14:22:53 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/29 18:41:47 by jatan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	free(token->value);
	free(content);
}

void	free_cmd_grp(void *content)
{
	int			i;
	t_cmd_grp	*cmd_grp;
	t_list		*node;
	t_list		*temp;

	i = 0;
	cmd_grp = (t_cmd_grp *)content;
	while (cmd_grp->args[i])
		free(cmd_grp->args[i++]);
	free(cmd_grp->args);
	node = cmd_grp->retokens;
	while (node)
	{
		temp = node->next;
		free(node);
		node = temp;
	}
	free(content);
}

void	free_env(void *content)
{
	char	**data;

	data = (char **)content;
	free(data[0]);
	free(data[1]);
	free(data);
}
