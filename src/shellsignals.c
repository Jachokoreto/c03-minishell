/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellsignals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:36:36 by leu-lee           #+#    #+#             */
/*   Updated: 2022/04/30 18:23:23 by leu-lee          ###   ########.fr       */
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
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
}

void	shellsignals(void)
{
	struct termios	termios_new;
	struct termios	termios_save;

	ft_tcgetattr(0, &termios_save);
	termios_new = termios_save;
	termios_new.c_lflag &= ~ECHOCTL;
	ft_tcsetattr(0, 0, &termios_new);
	signal(SIGQUIT, handler);
	signal(SIGINT, handler);
	return ;
}
