/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 22:12:24 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/28 11:38:32 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unlink(const char *pathname)
{
	if (unlink(pathname) == -1)
	{
		perror("Unlink failed");
		exit(errno);
	}
}

void	ft_dup(int oldfd)
{
	if (dup(oldfd) == -1)
	{
		perror("Dup failed");
		exit(errno);
	}
}

void	ft_free_all(t_data *data)
{
	ft_lstclear(&data->env_list, free_env);
	ft_lstclear(&data->tokens, free_token);
	ft_lstclear(&data->cmd_grps, free_cmd_grp);
	free_str_array(data->builtins);
	free_str_array(data->envp);
	free(data);
}

int	ft_chdir(const char *path)
{
	int	exit_status;

	exit_status = chdir(path);
	if (exit_status == -1)
	{
		perror("cd error");
		return (1);
	}
	return (0);
}

void	ft_free(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
}
