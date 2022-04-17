/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatan <jatan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 22:12:24 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/17 14:04:59 by jatan            ###   ########.fr       */
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

void ft_free_all(t_data *g_data)
{
	ft_lstclear(&g_data->env_list, free_env);
	ft_lstclear(&g_data->tokens, free_token);
	ft_lstclear(&g_data->cmd_grps, free_cmd_grp);
	free_str_array(g_data->builtins);
	free_str_array(g_data->envp);
	free(g_data);
}
