#include "minishell.h"

int	main(int argc, char **argv)
{	
	char	*line;

	while ((line = get_next_line(0)) != NULL)
	{
		read_commands(line);
		//printf("%s", line);
		free(line);
	}
	line = readline(line);
}