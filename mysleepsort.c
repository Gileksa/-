#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/wait.h>

int main(int ac, char *av[])
{
	int i, pid;
	int *w;

	for (i = 1; i < ac; i++)
	{
		pid = fork();
		if (pid == 0)
		{
			usleep(atol(av[i])*10000);
			printf("%s ", av[i]);
			exit(pid);
		}
	}

	//while ((*w) != -1)
	for (i = 1; i < ac; i++)
	{
		wait(w);
	}
	printf("\n");
	
	return 0;
}
