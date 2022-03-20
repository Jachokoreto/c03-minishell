#include "minishell.h"

void	cd(char **args)
{
	char	buf[256];
	(void)args;
	// getcwd(buf, sizeof(buf));
	// printf("%s\n", buf);
	chdir(args[0]);
	// getcwd(buf, sizeof(buf));
	// printf("%s\n", buf);
}
