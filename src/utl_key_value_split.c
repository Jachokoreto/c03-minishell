/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl_key_value_split.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 09:56:47 by jatan             #+#    #+#             */
/*   Updated: 2022/04/25 13:52:17 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**key_value_split(const char *s, char c)
{
	char	**table;
	size_t	index;

	index = 0;
	table = ft_calloc(3, sizeof(char *));
	if (!table)
		return (NULL);
	while (s[index] != c && s[index] != '\0')
		index++;
	if (s[index] == 0)
	{
		free(table);
		return (NULL);
	}
	index++;
	table[0] = ft_strndup(s, index - 1);
	table[1] = ft_strndup(s + index, ft_strlen(s) - index);
	table[2] = NULL;
	return (table);
}
