/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatan <jatan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:45:50 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/16 18:48:30 by jatan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	n_flag(char **args)
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
		while (args[i][0] == '-' && args[i][j] == 'n')
			j++;
		if (args[i][j] == '\0')
			newline_flag++;
		else
			return (i);
	}
	return (newline_flag);
}

int	echo(char **args, void *data)
{
	int	i;
	int	flag;

	i = 0;
	if (args[1] == NULL)
		return ;
	if (args[1][0] == '-')
		i = n_flag(args) - 1;
	flag = i;
	while (args[++i])
	{
		if (args[i][0] == '~')
			printf("%s", mini_getenv("HOME", data));
		else
			printf("%s", args[i]);
		if (args[i + 1] != NULL)
			printf(" ");
	}
	if (flag > 1)
		printf("\n");
	return (0);
}
