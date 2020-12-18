/*Напишите программу, экспериментально определяющую размер буфера, выделяемого операционной системой для организации pipe. Используйте факт блокировки процесса при заполнении буфера и параллельные процессы.*/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main(int ac, char *av[])
{
	int pipefd[2],p,counter = 0,wr;
	char s = 'x';
	
//нужно сделать pipe
	p = pipe2(pipefd, O_NONBLOCK);//чтобы процесс не блокировался
	if (p == -1)
	{
		perror("pipe error");
		return errno;
	}

//записывать по одному символу, пока есть место, и считать

	while((write(pipefd[1],&s,1)) == 1)
	{
		counter++;
	}	
	
	printf("Buffer size is %d\n", counter);

	return 0;
}
