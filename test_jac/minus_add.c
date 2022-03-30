#include <stdio.h>

int main(void)
{
	char str[] = {"hello"};

	printf("%d\n", 0 - &str);
}