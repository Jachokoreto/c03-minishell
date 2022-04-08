/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:44:55 by leu-lee           #+#    #+#             */
/*   Updated: 2022/03/31 18:17:26 by leu-lee          ###   ########.fr       */
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
	if (args[0][0] == '~')
		chdir(ft_strjoin(mini_getenv("HOME"), args[0] + 1));
	else
		chdir(args[0]);
	env = (t_env *)pwd->content;
	env->value = getcwd(NULL, 0);
}
