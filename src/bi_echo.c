/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatan <jatan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:45:50 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/16 16:50:37 by jatan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(char **args, void *data)
{
	int	i;
	int	n;

	(void)data;
	i = 0;
	if (!args[1])
		return (1);
	n = !utl_strncmp(args[1], "-n");
	while (args[++i + n + 1])
		printf("%s ", args[i + n]);
	printf("%s", args[i + n]);
	if (n == 0)
		printf("\n");
	return (0);
}
