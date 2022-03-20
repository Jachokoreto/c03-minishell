#include "minishell.h"

int	main(int argc, char **argv)
{	
	char	*line;
	t_temp	*temp;

	(void)argv;
	argc = 1;
	temp = init_mini();
	while (1)
	{
		line = readline("minishell > ");
		read_commands(temp, line);
	}
}
