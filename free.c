#include "stdlib.h"

int	main()
{
	char *str;

	str = malloc(sizeof(char));
	free(str);
	str = NULL;
	free(str);
}