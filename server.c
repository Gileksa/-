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
#include <sys/sem.h>
#include <sys/shm.h>

union semun 
{
	int val;
};

int main(int ac, char *av[])
{
	int id,p,semid;

	key_t key = ftok(server.c,1);//ключ для общей памяти
	if(key == -1)
	{
		perror(ftok error);
		return errno;
	}

	id = shmget(key,256, IPC_CREAT | 0777);//общая память создание
	if(id == -1)
	{
		perror(shmget error);
		return errno;
	}

	p = shmat(id,NULL,0700);//адрес общей памяти
	if(p == -1)
	{
		perror(shmat error);
		return errno;
	}
	
	//надо считывать из того общего куска памяти целую строку и выводить ее. надо семафор 

	semkey = ftok(server.c,2);
	semid = semget(semkey, 1, (IPC_CREAT | IPC_EXCL | 0700));//выделили для семафора
	if(semid == -1)
	{
		perror(semget error);
		return errno;
	}

	arg.val = 1;
	semctl(id, 0, SETVAL, arg);//семафор 1 когда буфер пустой. клиент делает -1

	


	return 0;
}
