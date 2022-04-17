/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl_env_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatan <jatan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 10:00:05 by jatan             #+#    #+#             */
/*   Updated: 2022/04/17 10:33:17 by jatan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**add_new_env(char **array, char *env)
{
	int		i;
	char	**new_env;

	i = 0;
	while (array[i] != NULL)
		i++;
	new_env = ft_calloc(i + 2, sizeof(char *));
	new_env[i] = ft_strdup(env);
	while (--i >= 0)
		new_env[i] = ft_strdup(array[i]);
	free_str_array(array);
	return (new_env);
}

char	**del_env(char **array, char *key)
{
	int		i;
	int		to_del;
	char	**new_env;

	i = 0;
	to_del = 0;
	while (array[i] != NULL)
	{
		if (ft_strncmp(key, array[i], ft_strlen(key)) == 0
			&& array[i][ft_strlen(key)] == '=')
			to_del = i;
		i++;
	}
	if (to_del == 0)
		return (array);
	new_env = ft_calloc(i, sizeof(char *));
	while (--i >= 0)
	{
		if (i != to_del)
			new_env[i - 1] = ft_strdup(array[i]);
	}
	free_str_array(array);
	return (new_env);
}

char	**set_env_array(char **array, char *env)
{
	int		i;
	char	**new_env;
	char	**env2;

	i = 0;
	env2 = key_value_split(env, '=');
	while (array[i] != NULL)
	{
		if (ft_strncmp(env2[0], array[i], ft_strlen(env2[0])) == 0
			&& array[i][ft_strlen(env2) + 1] == '=')
		{
			free(array[i]);
			array[i] = ft_strdup(env);
			return (array);
		}
		i++;
	}
	return (add_new_env(array, env));
}


