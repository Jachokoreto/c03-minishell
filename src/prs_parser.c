/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatan <jatan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 10:34:39 by jatan             #+#    #+#             */
/*   Updated: 2022/03/24 18:16:15 by jatan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	parser(char *line)
{
	t_list	*tmp;
	t_token	*tmp_token;

	mini_lexer(line);
	tmp = g_data->tokens;
	while (tmp)
	{
		tmp_token = tmp->content;
		printf("%d, |%s|\n", tmp_token->type, tmp_token->value);
		tmp = tmp->next;
	}
}
