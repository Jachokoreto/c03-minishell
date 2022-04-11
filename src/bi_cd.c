/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:44:55 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/09 18:09:41 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	cd(char **args)
// {
// 	static t_list	*oldpwd;
// 	static t_list	*pwd;
// 	t_list			*curnode;
// 	t_env			*env;

// 	curnode = g_data->env_list;
// 	if (oldpwd == NULL)
// 	{
// 		while (curnode)
// 		{
// 			env = (t_env *)curnode->content;
// 			if (ft_strncmp(env->key, "OLDPWD", ft_strlen("OLDPWD")) == 0)
// 				oldpwd = curnode;
// 			if (ft_strncmp(env->key, "PWD", ft_strlen("PWD")) == 0)
// 				pwd = curnode;
// 			curnode = curnode->next;
// 		}
// 	}
// 	env = (t_env *)oldpwd->content;
// 	env->value = getcwd(NULL, 0);
// 	if (args[1][0] == '~')
// 		chdir(ft_strjoin(mini_getenv("HOME"), args[1] + 1));
// 	else
// 		chdir(args[1]);
// 	env = (t_env *)pwd->content;
// 	env->value = getcwd(NULL, 0);
// }

void	cd(char **args)
{
	int				i;
	static char		*ori_home;

	if (ori_home == NULL)
		ori_home = ft_strdup(mini_getenv("HOME"));
	i = 0;
	while (args[i] != NULL)
		i++;
	if (i > 3)
		return ;
	if (i == 2)
	{
		if (args[1][0] == '~')
			chdir(ft_strjoin(mini_getenv("HOME"), args[1] + 1));
		else
			chdir(args[1]);
	}
	else if (i == 1)
	{
		if (mini_getenv("HOME") == NULL)
			perror("cd error");
		else
			chdir(mini_getenv("HOME"));
	}
}
