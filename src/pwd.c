#include "minishell.h"

void	pwd(char **args)
{
	char	buf[256];
	(void)args;

	getcwd(buf, sizeof(buf));
	printf("%s\n", buf);
}