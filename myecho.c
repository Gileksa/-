#include <stdio.h>
#include <string.h>

int main(int ac, char *av[])
{
	int i, k = 1, m = 0;
	if (strcmp(av[1], "-n") == 0)
	{
		k++;
		m++;
	}
	for (i = k; i < ac - 1; i++)
		printf("%s ", av[i]);
	printf("%s", av[ac - 1]);
	if(m == 0)
		printf("\n");
	return 0;
}
