/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:46:54 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/30 16:57:22 by leu-lee          ###   ########.fr       */
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
		if (ft_isalpha(args[1][i]) == 1)
		{
			ft_putstr_fd("exit : numeric argument required\n", 2);
			exit(255);
		}
		i++;
	}
	if (args[1] && args[2] != NULL)
	{
		g_exit = 1;
		ft_putstr_fd("exit : too many arguments\n", 2);
	}
	exit(ft_atoi(args[1]));
}
