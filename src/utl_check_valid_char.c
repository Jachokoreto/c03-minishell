/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl_check_valid_char.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 10:13:21 by leu-lee           #+#    #+#             */
/*   Updated: 2022/05/01 11:54:58 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Helper function to checking in unset and export base on bash criteria.
 */

int	check_valid_char(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (1);
	i++;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}
