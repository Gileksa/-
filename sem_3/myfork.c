#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int ac, char *av[])
{
	int i, pid, n = atol(av[ac - 1]);

	printf("parent %i\n", getpid());

	if (atol(av[1]) == 1)
	{
		for (i = 0; i < n; i++)
		{
			pid = fork();
			if (pid == 0)
			{
				printf("child %i %i\n", getpid(), getppid());
				_exit(getpid());
			}
		}
		return 0;
	}

	for (i = 0; i < n; i++)
		{
			pid = fork();
			if (pid != 0)
			{
				_exit(getpid());
			}
			printf("child %i %i\n", getpid(), getppid());
		}
		return 0;
	return 0;
}
