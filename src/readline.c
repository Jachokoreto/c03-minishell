#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(int argc, char **argv)
{	
	char	*str;
	if (argc != 2)
		return (0);
	while (1)
	{
		str = readline(argv[1]);
		printf("Readline yo: %s", str);
	}
}