#include "minishell.h"

void	echo(char **args)
{
	printf("%s\n", args[0]);
}