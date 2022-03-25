#include <stdio.h>

int main(int argc, char **argv)
{
	int i;

	printf("%d\n", argc - 1);
	
	i = 0;
	while (++i < argc)
		printf("%d. %s\n", i, argv[i]);
	return (0);
}