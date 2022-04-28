/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl_get_env_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 11:00:37 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/28 11:38:32 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_env_array(t_data *data)
{
	char	**arr;
	t_list	*node;
	t_env	*env;
	int		i;

	arr = NULL;
	i = 0;
	arr = ft_calloc(ft_lstsize(data->env_list) + 1, sizeof(char *));
	node = data->env_list;
	while (node)
	{
		env = node->content;
		arr[i] = join_key_value(env->key, env->value, '=');
		node = node->next;
	}
	return (arr);
}
