/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatan <jatan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:47:34 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/16 16:51:43 by jatan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


int	unset(char **args, void *g_data)
{
	t_env	*tmp;
	t_list	*curnode;
	t_list	*prevnode;

	while (args)
	{
		curnode = ((t_data *)g_data)->env_list;
		prevnode = NULL;
		while (curnode)
		{
			tmp = (t_env *)curnode->content;
			if (utl_strncmp(tmp->key, *(args++)) == 0)
			{
				if (prevnode == NULL)
					((t_data *)g_data)->env_list = curnode->next;
				else
					prevnode->next = curnode->next;
				ft_lstdelone(curnode, free_env);
				break ;
			}
			prevnode = curnode;
			curnode = curnode->next;
		}
	}
	return (0);
}
