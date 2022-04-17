/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl_init_mini.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatan <jatan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:45:37 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/17 10:39:23 by jatan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	init_exit_status(t_data *g_data)
// {
// 	;
// }


void	init_env(t_data	*g_data, char **envp)
{
	int		i;
	t_env	*env;
	char	**str;

	g_data->env_list = NULL;
	i = -1;
	while (envp[++i])
	{
		str = key_value_split(envp[i], '=');
		env = ft_calloc(1, sizeof(t_env));
		env->key = str[0];
		env->value = str[1];
		if (ft_strncmp(env->key, "OLDPWD", ft_strlen("OLDPWD")) == 0)
			env->value = getcwd(NULL, 0);
		ft_lstadd_back(&g_data->env_list, ft_lstnew(env));
	}
	i = 0;
	while (envp[i] != NULL)
		i++;
	g_data->env_array = ft_calloc(i + 1, sizeof(char *));
	while (--i >= 0)
		g_data->env_array[i] = ft_strdup(envp[i]);
}

t_data	*init_mini(char **envp)
{
	t_data	*g_data;

	g_data = (t_data *)ft_calloc(1, sizeof(t_data));
	g_data->builtins = ft_split("echo cd pwd export unset env exit", ' ');
	g_data->builtin_funcs[0] = echo;
	g_data->builtin_funcs[1] = cd;
	g_data->builtin_funcs[2] = pwd;
	g_data->builtin_funcs[3] = export;
	g_data->builtin_funcs[4] = unset;
	g_data->builtin_funcs[5] = env;
	g_data->builtin_funcs[6] = ft_exit;
	init_env(g_data, envp);
	return (g_data);
}
