/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:45:37 by leu-lee           #+#    #+#             */
/*   Updated: 2022/03/21 20:27:57 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// reminder that ft_split will fail if two or more '='(s) are found.

#include "minishell.h"

void	init_env(t_data	*data, char **envp)
{
	int		i;
	t_env	*env;
	char	**str;
	// char	buf[256];

	i = -1;
	while (envp[++i])
	{
		str = ft_split(envp[i], '=');
		env = malloc(sizeof(t_env));
		env->key = str[0];
		env->value = str[1];
		if (ft_strncmp(env->key, "OLDPWD", ft_strlen("OLDPWD")) == 0)
			env->value = getcwd(NULL, 0);
		ft_lstadd_back(&data->env_list, ft_lstnew(env));
	}
}

t_data	*init_mini(char **envp)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
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
