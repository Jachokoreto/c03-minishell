#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{	
	char	*line;

	(void)argv;
	argc = 1;
	data = init_mini(envp);
	while (1)
	{
		line = readline("Minishell > ");
		read_commands(data, line);
	}
}
