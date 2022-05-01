/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl_strncmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 11:02:54 by leu-lee           #+#    #+#             */
/*   Updated: 2022/05/01 11:51:39 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Helper function do some string comparison and shorten code.
 */

int	utl_strncmp(char *s1, char *s2)
{
	if (ft_strncmp(s1, s2, ft_strlen(s1)) == 0
		&& ft_strlen(s1) == ft_strlen(s2))
		return (0);
	return (1);
}
