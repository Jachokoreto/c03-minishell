/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:46:54 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/22 14:21:01 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	ft_exit(char **args, t_data *data)
{
	int	i;

	(void)data;
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
			exit(1);
		}
	}
	else
	{
		ft_putstr_fd("exit : too many arguments\n", 2);
		exit(1);
	}
	return (0);
}
