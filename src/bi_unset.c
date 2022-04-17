/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatan <jatan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:47:34 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/17 16:44:21 by jatan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

char	**del_env(char **old_env, char *key)
{
	int		i;
	int		to_del;
	char	**new_env;

	i = 0;
	to_del = -1;
	printf("%s\n", old_env[0]);
	printf("%s\n", key);

	while (old_env[i] != NULL)
	{
		if (ft_strncmp(key, old_env[i], ft_strlen(key)) == 0
			&& old_env[i][ft_strlen(key)] == '=')
			to_del = i;
		printf("%d\n", to_del);
		i++;
	}
	if (to_del == -1)
		return (old_env);
	new_env = ft_calloc(i, sizeof(char *));
	while (--i >= 0)
	{
		if (i != to_del)
			new_env[i - 1] = ft_strdup(old_env[i]);
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
