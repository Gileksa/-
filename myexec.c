#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <getopt.h>

int main(int ac, char *av[])
{
	char *avn[ac];
	
	int proc = 0,i = 0, w = 0, proc2 = 0, j = 0, go = 0, option_index;

	for (i = 0; i < ac - 1; i++)
	{
		avn[i] = av[i + 1];
	}
	avn[ac - 1] = NULL;

	static struct option long_options[] = 
	{
		{"wc", no_argument, 0, 'w'},
	};

	while (go != -1)
	{
		go = getopt_long(ac, av, "w", long_options, &option_index);
		switch (go)
		{
			case '?':
				printf("invalid option name");
				return 0;
			case 'w':
				w++;
				break;
		}
	}
	

	if (w != 0)
	{
		int pipefd[2], pp, proc, newfd, rd = 1, symb = 0, words = 1, str = 1;
		char buf[4096];


		pp = pipe(pipefd);
		proc = fork();
		if (proc == 0)
		{
			close(1);
			newfd = dup(pipefd[1]);
			close(pipefd[0]);
			close(pipefd[1]);
			
			execvp(avn[1], avn + 1);
			
			perror("error");
		}
		
		close(pipefd[1]);
		
		while(rd >0 )
		{	
			rd = read(pipefd[0], buf, 1);
			symb+=rd;
			if(buf[symb] == ' ')
				words++;
			if(buf[symb] == '\n')
				str++;
			//slova i stroki
		}

		printf("%i bytes\n%i words\n%i strings\n", symb, words, str);
		close(pipefd[0]);

		return 0;
	}

	struct timespec time1;
	struct timespec time2;
	
	clock_gettime(CLOCK_REALTIME, &time1);

	proc = fork();
	if (proc == 0)
	{
		execvp(av[1], avn);
		_exit(getpid());
	}

//	while (w != -1)
//	{
		wait(&w);
//	}

	clock_gettime(CLOCK_REALTIME, &time2);

	printf("\n%ld microsec\n", ((time2.tv_sec - time1.tv_sec)*1000000 + (time2.tv_nsec - time1.tv_nsec)/1000));

	return 0;
}
