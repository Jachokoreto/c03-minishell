/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:44:55 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/28 10:57:59 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_dir(char *name, char **envp, char *arg)
{
	char	*tmp1;
	char	*tmp2;

	if (arg == NULL)
		return (mini_getenv(name, envp));
	tmp1 = mini_getenv(name, envp);
	if (tmp1 == NULL)
		return (NULL);
	tmp2 = ft_strjoin(tmp1, arg);
	free(tmp1);
	return (tmp2);
}

int	process_cd(char **args, char **envp)
{
	char	*dir;
	int		ret;

	if (args[1] != NULL)
	{
		if (args[1][0] == '~')
			dir = get_dir("HOME", envp, args[1] + 1);
		else if (args[1][0] == '-' && args[1][1] == '\0')
			dir = get_dir("OLDPWD", envp, args[1] + 1);
		else
			dir = ft_strdup(args[1]);
	}
	else
		dir = mini_getenv("HOME", envp);
	if (dir == NULL)
	{
		ft_putstr_fd("cd error: HOME not set\n", 2);
		return (1);
	}
	ret = ft_chdir(dir);
	free(dir);
	return (ret);
}

int	cd(char **args, t_data *data)
{
	char		*tmps[3];
	char		*tmp;

	tmps[2] = NULL;
	tmps[0] = ft_strdup("export");
	tmp = getcwd(NULL, 0);
	tmps[1] = join_key_value("OLDPWD", tmp, '=');
	g_exit = process_cd(args, data->envp);
	export(tmps, data);
	free(tmp);
	free(tmps[2]);
	tmp = getcwd(NULL, 0);
	free(tmps[1]);
	tmps[1] = join_key_value("PWD", tmp, '=');
	export(tmps, data);
	free(tmp);
	free(tmps[0]);
	free(tmps[1]);
	free(tmps[2]);
	return (g_exit);
}
