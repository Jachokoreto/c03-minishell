#include <minishell.h>

void	handler(int signo)
{
	if (signo == SIGQUIT)
	{
		// write(1, "\nMinishell >", 14);
		// rl_on_new_line();
		return ;
	}
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		ft_strlcpy(rl_prompt, "hihi", 5);
		rl_replace_line("", 0);
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
