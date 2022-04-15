/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 22:12:24 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/11 22:19:17 by leu-lee          ###   ########.fr       */
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
