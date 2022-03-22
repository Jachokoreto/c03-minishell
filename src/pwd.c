/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:47:28 by leu-lee           #+#    #+#             */
/*   Updated: 2022/03/22 16:40:29 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(char **args)
{
	// static int	i;
	char		*buf;

	(void)args;
	// while (args)
	// 	i++;
	//printf("i: %d\n", i);
	buf = getcwd(NULL, 0);
	printf("%s\n", buf);
}
