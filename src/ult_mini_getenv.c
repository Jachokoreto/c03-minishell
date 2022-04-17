/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ult_mini_getenv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatan <jatan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 09:47:12 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/17 10:40:14 by jatan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// char	*mini_getenv(char *key, t_list *env_list)
// {
// 	t_list	*node;
// 	t_env	*env;

// 	node = env_list;
// 	while (node)
// 	{
// 		env = node->content;
// 		if (utl_strncmp(env->key, key) == 0)
// 			return (env->value);
// 		node = node->next;
// 	}
// 	return (NULL);
// }

char	*mini_getenv(char *key, char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(key, envp[i], ft_strlen(key)) == 0
			&& envp[i][ft_strlen(key) + 1] == '=')
			return (ft_strdup(&envp[i][ft_strlen(key) + 2]));
		i++;
	}
	return (NULL);
}
