/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl_move_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 15:24:43 by leu-lee           #+#    #+#             */
/*   Updated: 2022/05/01 11:50:38 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Helper function to dup and close.
 */

void	utl_move_fd(int fd1, int fd2)
{
	ft_dup2(fd1, fd2);
	ft_close(fd1);
}
