#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int ac, char *av[])
{
	int proc = 0,i = 0, w = 0;
	struct timespec time1;
	struct timespec time2;
	char *avn[ac];

	for (i = 0; i < ac - 1; i++)
	{
		avn[i] = av[i + 1];
	}
	avn[ac - 1] = NULL;
	
	clock_gettime(CLOCK_REALTIME, &time1);

	proc = fork();
	if (proc == 0)
	{
		execvp(av[1], avn);
	}

//	while (w != -1)
//	{
		wait(&w);
//	}

	clock_gettime(CLOCK_REALTIME, &time2);

	printf("\n%ld microsec\n", ((time2.tv_sec - time1.tv_sec)*1000000 + (time2.tv_nsec - time1.tv_nsec)/1000));

	return 0;
}
