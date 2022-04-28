/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:46:54 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/28 10:21:52 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char **args, t_data *data)
{
	int	i;

	(void)data;
	if (args[1] == NULL)
		exit(0);
	if (args[1] && args[2] == NULL)
	{
		i = 0;
		while (args[1][i] != 0 && ft_isdigit(args[1][i]) == 1)
			i++;
		if ((int)ft_strlen(args[1]) == i)
			exit(ft_atoi(args[1]));
		else
		{
			ft_putstr_fd("exit : numeric argument required\n", 2);
			exit(255);
		}
	}
	else
	{
		g_exit = 1;
		ft_putstr_fd("exit : too many arguments\n", 2);
	}
	return (0);
}
