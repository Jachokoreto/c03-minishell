/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl_free_str_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 20:18:44 by jatan             #+#    #+#             */
/*   Updated: 2022/04/25 10:29:10 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
