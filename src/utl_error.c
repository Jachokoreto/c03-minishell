/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 14:44:24 by jatan             #+#    #+#             */
/*   Updated: 2022/05/01 11:52:57 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Helper function to prompt error message and return error number.
 */

int	utl_error(char *msg, int error_num)
{
	g_exit = error_num;
	ft_putstr_fd(msg, 2);
	return (g_exit);
}
