/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatan <jatan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:44:55 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/15 17:12:24 by jatan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_cd(char **args, t_list *env_list)
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
			chdir(ft_strjoin(mini_getenv("HOME", env_list), args[1] + 1));
		else if (args[1][0] == '-')
			chdir(ft_strjoin(mini_getenv("OLDPWD", env_list), args[1] + 1));
		else
			chdir(args[1]);
	}
	else if (i == 1)
	{
		if (mini_getenv("HOME", env_list) == NULL)
			perror("cd error");
		else
			chdir(mini_getenv("HOME", env_list));
	}
}

void	cd(char **args, void *data)
{
	t_list		*lst;
	static char	*ori_home;

	lst = ((t_data *)data)->env_list;
	set_env(lst, "OLDPWD", getcwd(NULL, 0));
	if (ori_home == NULL)
		ori_home = ft_strdup(mini_getenv("HOME", lst));
	process_cd(args, lst);
	set_env(lst, "PWD", getcwd(NULL, 0));
}
