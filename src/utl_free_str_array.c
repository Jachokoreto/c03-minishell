/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl_free_str_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 20:18:44 by jatan             #+#    #+#             */
/*   Updated: 2022/05/01 11:52:10 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Helper function free a double pointer array.
 */

void	free_str_array(char **str)
{
	char	**tmp;

	tmp = str;
	while (tmp && *tmp)
	{
		free(*tmp);
		tmp++;
	}
	free(str);
}
