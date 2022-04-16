/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl_set_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatan <jatan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 10:16:28 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/16 16:08:12 by jatan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_env(t_list *lst, char *key, char *value)
{
	t_env	*tmp;

	while (lst)
	{
		tmp = (t_env *)lst->content;
		if (utl_strncmp(tmp->key, key) == 0)
		{
			tmp->value = value;
			return ;
		}
		lst = lst->next;
	}
	tmp = ft_calloc(1, sizeof(t_env));
	tmp->key = key;
	tmp->value = value;
	ft_lstadd_back(&lst, ft_lstnew(tmp));
}
