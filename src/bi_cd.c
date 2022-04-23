/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:44:55 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/23 12:05:01 by leu-lee          ###   ########.fr       */
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
	tmp2 = ft_strjoin(tmp1, arg);
	free(tmp1);
	return (tmp2);
}


// ft_chdir returns int, update the exit status through there.
void	process_cd(char **args, char **envp)
{
	char	*dir;

	if (args[2] != NULL)
		return ;
	if (args[1] != NULL)
	{
		if (args[1][0] == '~')
			dir = get_dir("HOME", envp, args[1] + 1);
		else if (args[1][0] == '-')
			dir = get_dir("OLDPWD", envp, args[1] + 1);
		else
		{
			dir = ft_strdup(args[1]);
			// tmp = ft_strdup(args[1]);
		}
		// free(tmp);
	}
	else
	{
		dir = mini_getenv("HOME", envp);
		if (dir == NULL)
			perror("cd error HOME Unavailable");
	}
	chdir(dir);
	free(dir);
}

int	cd(char **args, t_data *data)
{
	char		*tmp1;
	char		*tmp2;

	tmp1 = getcwd(NULL, 0);
	tmp2 = ft_strjoin("OLDPWD", tmp1);
	process_cd(args, data->envp);
	export(&tmp2, data);
	free(tmp1);
	free(tmp2);
	tmp1 = getcwd(NULL, 0);
	tmp2 = ft_strjoin("PWD", tmp1);
	export(&tmp2, data);
	free(tmp1);
	free(tmp2);
	return (0);
}
