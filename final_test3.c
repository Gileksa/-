/*Напишите программу, экспериментально определяющую размер буфера, выделяемого операционной системой для организации pipe. Используйте факт блокировки процесса при заполнении буфера и параллельные процессы.*/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>

int main(int ac, char *av[])
{
	int pipefd[2],p,counter = 0,w,i,cnt = counter,pid;
	char s = 'x';
	
	p = pipe(pipefd);
	if (p == -1)
	{
		perror("pipe error");
		return errno;
	}

	p = fork();
	if(p == 0)
	{
		pid = getpid();
		for(i = 0; i >= 0; i++)
		{
			write(pipefd[1],&s,1);
			counter++;
		}//в какой-то момент блокируется
	}
	
	while(1)
	{
		sleep(5);
	}

	kill(pid, SIGUSR1);

	printf("Buffer size is %d\n", counter);

	return 0;
}
