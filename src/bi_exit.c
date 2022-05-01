/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:46:54 by leu-lee           #+#    #+#             */
/*   Updated: 2022/05/01 12:43:01 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char **args, t_data *data)
{
	int	i;

	(void)data;
	if (args[1] == NULL)
	{
		printf("exit\n");
		exit(0);
	}
	printf("exit\n");
	i = 0;
	while (args[1][i])
	{
		if (!(ft_isdigit(args[1][i]) == 1))
			exit(utl_error("exit : numeric argument required\n", 255));
		i++;
	}
	if (args[1] && args[2] != NULL)
		return (utl_error("exit : too many arguments\n", 1));
	exit(ft_atoi(args[1]));
}
