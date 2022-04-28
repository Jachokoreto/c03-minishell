/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl_init_mini.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:45:37 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/28 11:38:32 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env(t_data	*data, char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	data->envp = ft_calloc(i + 1, sizeof(char *));
	data->envp[i] = NULL;
	while (--i >= 0)
		data->envp[i] = ft_strdup(envp[i]);
}

t_data	*init_mini(char **envp)
{
	t_data	*data;

	g_exit = 0;
	data = (t_data *)ft_calloc(1, sizeof(t_data));
	data->builtins = ft_split("echo cd pwd export unset env exit", ' ');
	data->builtin_funcs[0] = echo;
	data->builtin_funcs[1] = cd;
	data->builtin_funcs[2] = pwd;
	data->builtin_funcs[3] = export;
	data->builtin_funcs[4] = unset;
	data->builtin_funcs[5] = env;
	data->builtin_funcs[6] = ft_exit;
	init_env(data, envp);
	return (data);
}
