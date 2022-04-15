/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ult_mini_getenv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 09:47:12 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/15 11:06:48 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*mini_getenv(char *key)
{
	t_list	*node;
	t_env	*env;

	node = g_data->env_list;
	while (node)
	{
		env = node->content;
		if (utl_strncmp(env->key, key) == 0)
			return (env->value);
		node = node->next;
	}
	return (NULL);
}
