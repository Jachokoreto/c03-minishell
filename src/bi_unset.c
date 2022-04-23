/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatan <jatan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:47:34 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/23 11:14:17 by jatan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_to_del_env(char **old_env, char *key, int *i)
{
	int		to_del;

	to_del = -1;
	while (old_env[*i] != NULL)
	{
		if (ft_strncmp(key, old_env[*i], ft_strlen(key)) == 0
			&& old_env[*i][ft_strlen(key)] == '=')
			to_del = *i;
		(*i)++;
	}
	return (to_del);
}

char	**del_env(char **old_env, char *key)
{
	int		i;
	int		j;
	int		to_del;
	char	**new_env;

	i = 0;
	to_del = get_to_del_env(old_env, key, &i);
	if (to_del == -1)
		return (old_env);
	new_env = ft_calloc(i, sizeof(char *));
	j = i - 1;
	while (--i >= 0)
	{
		if (i != to_del)
			new_env[--j] = ft_strdup(old_env[i]);
	}
	free_str_array(old_env);
	return (new_env);
}

int	unset(char **args, t_data *data)
{
	(void)data;
	while (++args && *args != 0)
	{
		data->envp = del_env(data->envp, *args);
	}
	return (0);
}
