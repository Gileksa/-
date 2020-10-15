#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <getopt.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

struct mes {
	long type;
	int mtext;
};

int judge(int n, int id)
{
	struct mes prishel;
	struct mes pribezhal;
	static struct timespec start;
	static struct timespec finish;

	int i,mes1,mes2,mes3,mes4;
	printf("The judge is here\n");
	
	for(i = 0; i < n; i++)
	{
		mes1 = msgrcv(id, &prishel, sizeof(struct mes),1,0);
		if(mes1 == -1)
		{
			perror("judmes1 error");
			return errno;
		}
		printf("%d is here\n", i);
	}

	printf("ready, go!\n");

	clock_gettime(CLOCK_REALTIME, &start);

	for(i = 0; i < n; i++)
	{
		struct mes run = {2,i};
		

		mes2 = msgsnd(id, &run, sizeof(struct mes), 0);
		if(mes2 == -1)
		{
			perror("judmes2 error");
			return errno;
		}

		printf("%d is rinnung\n", i);

		mes3 = msgrcv(id, &pribezhal, sizeof(struct mes),3,0);
		
		if(mes3 == -1)
		{
			perror("judmes3 error");
			return errno;
		}
		printf("%d come\n", i);
	}
	clock_gettime(CLOCK_REALTIME, &finish);

	printf("Great results! Your time is %ld microsec. You can go home\n", ((finish.tv_sec - start.tv_sec)*1000000 + (finish.tv_nsec - start.tv_nsec)/1000));
	for(i = 0; i < n; i++)
	{
		struct mes home = {4,i};
		mes4 = msgsnd(id, &home, sizeof(struct mes), 0);
		if(mes4 == -1)
		{
			perror("judmes4 error");
			return errno;
		}
	}
	return 0;
}


int runner(int i, int id)
{
	struct mes prishel = {1,i}, finished = {3,i};
	struct mes run, home;

	printf("I'm %d\n", i);
	int mes1 = msgsnd(id, &prishel, sizeof(struct mes), 0);
	if(mes1 == -1)
	{
		perror("runmes1 error");
		return errno;
	}

	int mes2 = msgrcv(id, &run, sizeof(struct mes),2,0);
	if(mes2 == -1)
	{
		perror("runmes2 error");
		return errno;
	}
	printf("I'm %d, I'm running\n", i);

	int mes3 = msgsnd(id, &finished, sizeof(struct mes), 0);
	if(mes3 == -1)
	{
		perror("runmes3 error");
		return errno;
	}

	int mes4 = msgrcv(id, &home, sizeof(struct mes),4,0);
	if(mes4 == -1)
	{
		perror("runmes4 error");
		return errno;
	}
	printf("%d go home\n", i);
	return 0;
}


int main(int ac, char *av[])
{	
	int n = atoi(av[1]),w = 42;
	
	setbuf(stdout, NULL); //не буферизуем вывод
	struct msqid_ds buf; //открыли очередь
	
	int id = msgget(IPC_PRIVATE, (IPC_CREAT | IPC_EXCL | 0700));
	if(id == -1)
	{
		perror("get error");
		return errno;
	}

	int j;
	int jud = fork();
	if (jud == 0)
	{
		j = judge(n,id);
		if(j != 0)
		{
			perror("judge error");
			return errno;
		}
		exit(0);
	}

	int i,run,r;
	for(i = 0; i < n; i++)
	{
		run = fork();
		if(run == 0)
		{
			r = runner(i,id);
			if(r != 0)
			{
				perror("runner error");
				return errno;
			}
			exit(0);
		}
	}

	while(wait(&w) != -1)
	{
		//w = wait(&w);
	}

	int cls = msgctl(id,IPC_RMID, &buf); //почистили очередь
	if(cls == -1)
	{
		perror("ctl error");
		return errno;
	}
	

	return 0;
}
