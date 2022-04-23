/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl_init_mini.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatan <jatan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:45:37 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/23 14:46:40 by jatan            ###   ########.fr       */
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

	i = 0;
	while (envp[i] != NULL)
		i++;
	// i++;
	// g_data->envp = ft_calloc(i + 2, sizeof(char *));
	g_data->envp = ft_calloc(i + 1, sizeof(char *));
	g_data->envp[i] = NULL;
	// g_data->envp[--i] = ft_strdup("?=0");
	while (--i >= 0)
		g_data->envp[i] = ft_strdup(envp[i]);
}

t_data	*init_mini(char **envp)
{
	t_data	*g_data;

	g_exit = 0;
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
