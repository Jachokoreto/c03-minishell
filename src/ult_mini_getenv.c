/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ult_mini_getenv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatan <jatan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 09:47:12 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/15 17:09:09 by jatan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*mini_getenv(char *key, t_list *env_list)
{
	t_list	*node;
	t_env	*env;

	node = env_list;
	while (node)
	{
		env = node->content;
		if (utl_strncmp(env->key, key) == 0)
			return (env->value);
		node = node->next;
	}
	return (NULL);
}
