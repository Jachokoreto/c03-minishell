/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 17:23:09 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/14 12:10:07 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_path(char **input)
{
	char	**path;
	char	**envp;
	int		i;
	char	*cmd;

	envp = get_env_array();
	path = ft_split(mini_getenv("PATH"), ':');
	i = 0;
	if (execve(input[0], input, envp) == -1)
	// 	ft_execve(input[0], input, envp);
	{
	// else
	// {
		while (path[i])
		{
			cmd = join_key_value(path[i++], input[0], '/');
			execve(cmd, input, envp);
			free(cmd);
		}
	}
	return ;
	// }
	// free_str_array(envp);
}
