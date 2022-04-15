/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:45:50 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/15 17:26:29 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	no_newline(char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args[++i])
	{
		// seg faults if -nnaaa
		j = 1;
		while (args[++i][j] == 'n' && args[++i + 1] != NULL)
		{
			j++;
			printf("%s ", args[i]);
		}
		printf("%s", args[i]);
	}
	return ;
}

void	echo(char **args)
{
	int	i;

	if (!args[1])
		return ;
	if (args[1][0] == '~')
	{
		printf("%s\n", mini_getenv("HOME"));
		return ;
	}
	i = 0;
	if (args[1][0] != '-')
	{
		while (args[++i])
			printf("%s ", args[i]);
		printf("\n");
		return ;
	}
	else
		no_newline(args);
}
