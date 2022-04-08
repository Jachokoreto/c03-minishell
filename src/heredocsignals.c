#include <minishell.h>

void	herehandler(int signo)
{
	if (signo == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
	if (signo == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
}

void	heredocsignals(void)
{
	signal(SIGQUIT ,herehandler);
	signal(SIGINT ,herehandler);
	return ;
}
