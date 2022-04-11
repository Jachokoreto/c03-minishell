/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:45:50 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/11 15:37:49 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(char **args)
{
	int	i;
	int	n;

	i = 0;
	if (!args[1])
		return ;
	n = !utl_strncmp(args[1], "-n");
	while (args[++i + n + 1])
		printf("%s ", args[i + n]);
	printf("%s", args[i + n]);
	if (n == 0)
		printf("\n");
}
