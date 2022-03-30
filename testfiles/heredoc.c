# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

void	heredoc(char *delim)
{
	char	*line;
	if (delim == NULL)
		return ; 
	while (1)
	{
		line = get_next_line(0);
		if (line == NULL)
			continue ;
		if (line == delim)
			break ;
	}
}
