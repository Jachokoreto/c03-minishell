/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:44:55 by leu-lee           #+#    #+#             */
/*   Updated: 2022/03/29 12:45:31 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	cd(char **args)
{
	static t_list	*oldpwd;
	static t_list	*pwd;
	t_list			*curnode;
	t_env			*env;

	curnode = g_data->env_list;
	if (oldpwd == NULL)
	{
		while (curnode)
		{
			env = (t_env *)curnode->content;
			if (ft_strncmp(env->key, "OLDPWD", ft_strlen("OLDPWD")) == 0)
				oldpwd = curnode;
			if (ft_strncmp(env->key, "PWD", ft_strlen("PWD")) == 0)
				pwd = curnode;
			curnode = curnode->next;
		}
	}
	env = (t_env *)oldpwd->content;
	env->value = getcwd(NULL, 0);
	chdir(args[0]);
	env = (t_env *)pwd->content;
	env->value = getcwd(NULL, 0);
}
