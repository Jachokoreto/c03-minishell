/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 17:23:09 by leu-lee           #+#    #+#             */
/*   Updated: 2022/03/29 12:49:02 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_path(char *input)
{
	char	**path;
	char	**envp;
	int		i;
	char	*cmd = NULL;
	char	*argvec[] = {cmd, NULL};

	envp = get_env_array();
	path = ft_split(mini_getenv("PATH"), ':');
	i = 0;
	while (path)
	{
		cmd = join_key_value(path[i++], input, '/');
		argvec[0] = cmd;
		execve(cmd, argvec, envp);
	}
}
