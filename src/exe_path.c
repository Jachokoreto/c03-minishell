/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatan <jatan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 17:23:09 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/16 15:19:25 by jatan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_path(char **input, char **envp, char **path)
{
	int		i;
	char	*cmd;

	if (execve(input[0], input, envp) == -1)
	{
		i = 0;
		while (path[i])
		{
			cmd = join_key_value(path[i++], input[0], '/');
			execve(cmd, input, envp);
			free(cmd);
		}
	}
	return ;
}
