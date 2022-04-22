/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:44:55 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/17 16:32:19 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// ft_chdir returns int, update the exit status through there.
void	process_cd(char **args, char **envp)
{
	int		i;
	char	*tmp;

	i = 0;
	while (args[i] != NULL)
		i++;
	if (i >= 2)
	{
		if (args[1][0] == '~')
			tmp = ft_strjoin(mini_getenv("HOME", envp), args[1] + 1);
		else if (args[1][0] == '-')
			tmp = ft_strjoin(mini_getenv("OLDPWD", envp), args[1] + 1);
		else
			tmp = ft_strdup(args[1]);
		ft_chdir(tmp);
		free(tmp);
	}
	else if (i == 1)
	{
		if (mini_getenv("HOME", envp) == NULL)
			perror("cd error");
		else
			chdir(mini_getenv("HOME", envp));
	}
}

int	cd(char **args, void *data)
{
	char		***envp;
	static char	*ori_home;
	char		*tmp1;

	envp = &((t_data *)data)->envp;
	// set_env(lst, "OLDPWD", getcwd(NULL, 0));
	tmp1 = getcwd(NULL, 0);
	*envp = set_env_array(*envp, "OLDPWD", tmp1);
	free(tmp1);
	if (ori_home == NULL)
		ori_home = mini_getenv("HOME", *envp);
	process_cd(args, *envp);
	// set_env(lst, "PWD", getcwd(NULL, 0));
	tmp1 = getcwd(NULL, 0);
	*envp = set_env_array(*envp, "PWD", tmp1);
	free(tmp1);
	return (0);
}
