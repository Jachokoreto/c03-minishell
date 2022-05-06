/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellsignals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leu-lee <leu-lee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:36:36 by leu-lee           #+#    #+#             */
/*   Updated: 2022/05/06 11:05:04 by leu-lee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handler(int signo)
{
	if (signo == SIGINT)
	{
		g_exit = 1;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
}

/**
 * Signals that handles CTRL-C and CTRL-/
 * The termios is also handled here to prevent things like ^C from occuring.
 */

void	shellsignals(void)
{
	struct termios	termios_new;
	struct termios	termios_save;

	ft_tcgetattr(0, &termios_save);
	termios_new = termios_save;
	termios_new.c_lflag &= ~ECHOCTL;
	ft_tcsetattr(0, 0, &termios_new);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handler);
	return ;
}
