/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:44:55 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/15 11:05:26 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_cd(char **args)
{
	int	i;

	i = 0;
	while (args[i] != NULL)
		i++;
	if (i > 3)
		return ;
	if (i == 2)
	{
		if (args[1][0] == '~')
			chdir(ft_strjoin(mini_getenv("HOME"), args[1] + 1));
		else if (args[1][0] == '-')
			chdir(ft_strjoin(mini_getenv("OLDPWD"), args[1] + 1));
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

void	cd(char **args)
{
	t_list		*lst;
	static char	*ori_home;

	lst = g_data->env_list;
	set_env(lst, "OLDPWD", getcwd(NULL, 0));
	if (ori_home == NULL)
		ori_home = ft_strdup(mini_getenv("HOME"));
	process_cd(args);
	set_env(lst, "PWD", getcwd(NULL, 0));
}
