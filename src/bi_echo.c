/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatan <jatan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:45:50 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/17 12:30:44 by jatan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	n_flag(char **args)
{
	int	i;
	int	j;
	int	newline_flag;

	i = 0;
	newline_flag = 0;
	while (args[++i])
	{
		j = 1;
		while (args[i][0] == '-' && args[i][j] == 'n')
			j++;
		if (args[i][j - 1] == 'n' && args[i][j] == '\0')
			newline_flag++;
		else
			break ;
	}
	return (newline_flag);
}

int	echo(char **args, void *data)
{
	int	i;
	int	flag;

	if (args[1] == NULL)
		return (1);
	flag = n_flag(args);
	i = flag;
	while (args[++i])
	{
		if (args[i][0] == '~')
			printf("%s", mini_getenv("HOME", ((t_data *)data)->envp));
		else
			printf("%s", args[i]);
		if (args[i + 1] != NULL)
			printf(" ");
	}
	if (flag == 0)
		printf("\n");
	return (0);
}
