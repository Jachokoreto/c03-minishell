#include <stdio.h>

int main(void)
{
	int a = 5;
	int	qt = 0;

	qt = (qt != a) * qt + (qt != a && qt == 0) * a;
	printf("a:%d  qt:%d\n", a, qt);

	qt = (qt != a) * qt + (qt != a && qt == 0) * a;
	printf("a:%d  qt:%d\n", a, qt);

	qt = (qt != a) * qt + (qt != a && qt == 0) * a;
	printf("a:%d  qt:%d\n", a, qt);

	a = 10;

	qt = (qt != a) * qt + (qt != a && qt == 0) * a;
	printf("a:%d  qt:%d\n", a, qt);

	qt = (qt != a) * qt + (qt != a && qt == 0) * a;
	printf("a:%d  qt:%d\n", a, qt);

	a = 5;

	qt = (qt != a) * qt + (qt != a && qt == 0) * a;
	printf("a:%d  qt:%d\n", a, qt);

	a = 10;
	qt = (qt != a) * qt + (qt != a && qt == 0) * a;
	printf("a:%d  qt:%d\n", a, qt);
}