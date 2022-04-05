/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellsignals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:36:36 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/04 15:24:01 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handler(int signo)
{
	if (signo == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		ft_memmove(rl_line_buffer, "", 1);
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
}

void	shellsignals(void)
{
	signal(SIGQUIT ,handler);
	signal(SIGINT ,handler);
	return ;
}
