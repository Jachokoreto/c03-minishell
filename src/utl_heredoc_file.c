/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl_heredoc_files.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 10:37:23 by leu-lee           #+#    #+#             */
/*   Updated: 2022/05/06 10:38:49 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*heredoc_file(int i)
{
	char	*str;
	char	*index;

	index = ft_itoa(i);
	str = ft_strjoin(".heredocfile", index);
	free(index);
	return (str);
}
