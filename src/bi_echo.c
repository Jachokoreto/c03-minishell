/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:45:50 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/16 14:56:06 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	with_n_flag(char **args)
{
	int	i;
	int	j;
	int	newline_flag;
	int	count;

	i = 0;
	newline_flag = 0;
	count = 1;
	while (args[++i])
	{
		j = 1;
		while (args[i][j] == 'n')
			j++;
		if (args[i][j] == '\0')
		{
			count++;
			newline_flag = 1;
		}
		else
		{
			while (args[count] && args[count + 1] != NULL)
			{
				printf("%s ", args[count]);
				count++;
			}
			if (newline_flag == 1)
				printf("%s", args[count]);
			else
				printf("%s\n", args[count]);
			return ;
		}
	}
	while (args[i++])
		printf("%s ", args[count]);
	printf("%s", args[count]);
}

void	echo(char **args)
{
	int	i;

	i = 0;
	if (args[1] == NULL)
		return ;
	if (args[1][0] != '-')
	{
		while (args[++i])
		{
			if (args[i][0] == '~')
				printf("%s", mini_getenv("HOME"));
			else
				printf("%s", args[i]);
			if (args[i + 1] != NULL)
				printf(" ");
			else
				printf("\n");
		}
	}
	else
		with_n_flag(args);
}
