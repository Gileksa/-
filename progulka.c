//прогулочный теплоход, реализовать через семафоры

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <getopt.h>
#include <sys/ipc.h>
#include <errno.h>
#include <sys/sem.h>

int operation(int id, int semnum, int op)
{
	struct sembuf sem = {semnum, op, 0};
	int err = semop(id, &sem, 1);
	if(err == -1)
		return -1;
	return 0;
}

int capitan(int id, int travels)
{
	int i,er;
	
	//for(i = travels; i > 0; i--)//пока не кончились поездки
	//{
		//надо опустить трап и пригласить пассажиров. пока трап опущен, процесс должен блокироваться. в самом начале трап поднят
		printf("Please take your sits!\n");
		er = operation(id, 0, -1);//получился 0, процесс приостановился
		if (er == -1)
		{
			perror("1 error");
			return errno;
		}
		/*er = operation(sem, id, 1, 0);//ждем пока кораблик заполнится
		if (er == -1)
		{
			perror("7 error");
			return errno;
		}
		er = operation(sem, id, 3, 1);//кораблик отплыл
		if (er == -1)
		{
			perror("7 error");
			return errno;
		}

		printf("Travel started\n");*/

//до приплыть обратно и разгрузиться
//зациклить для всех поездок. В начале цикла проверять, израсходованы ли поездки. Если да, трап не опускать
	//}

	//operation

	return 0;
}

int tourist(int i, int id)
{	
	int er = 0;
	
	while(1)
	{
		er = operation(id,0,0);//почему оно здесь ломается???
		if (er < 0)
		{
			perror("2 error");
			return errno;
		}

		/*er = operation(sem,id,1,-1);//проверка наличия свободных мест
		if (er == -1)
		{
			perror("3 error");
			return errno;
		}
		er = operation(sem,id,2,-1);//если места есть, пассажир зашел на трап
		if (er == -1)
		{
			perror("4 error");
			return errno;
		}

		printf("%d is on ladder\n", i);
		
		er = operation(sem,id,2,1);//сошел с трапа на корабль
		if (er == -1)
		{
			perror("5 error");
			return errno;
		}

		printf("%d is on ship\n", i);

		er = operation(sem,id,3,0);//ждет начала поездки
		if (er == -1)
		{
			perror("6 error");
			return errno;
		}*/
	//дождаться конца поездки, выйти с лодки и сказать спасибо
	}
	return 0;
}


int main(int ac, char *av[])
{	
	int id, cap,c, tour, w = 42,i,t,err; 
	int nsem = 4;//nsem --- количество семафоров

	int tourists = atoi(av[1]);//количество отдыхающих
	int ladder = atoi(av[2]);//вместимость трапа
	int ship = atoi(av[3]);//вместимость кораблика
	int travels = atoi(av[4]);//количество поездок

	if(ladder > ship)
		ladder = ship; // смысла запускать на трап больше людей, чем уместится на паром

	setbuf(stdout, NULL);//дебуферизация вывода

	id = semget(IPC_PRIVATE, nsem, 0777); //открыли очередь семафоров
	if (id == -1)
	{
		perror("id error");
		return errno;
	}

	struct sembuf sem; //структура, через которую можно будет проверять семафоры и инициализировать их


///////////////////////// тут надо проинициализировать семафоры ///////////////////////////////////
	
// 0: трап опущен: 0, поднят: 1	
	err = operation(id, 0, 1);
	if (err == -1)
	{
		perror("init0 error");
		return errno;
	}
// 1: количество свободных мест на лодке
	err = operation(id, 1, ship);
	if (err == -1)
	{
		perror("init1 error");
		return errno;
	}
// 2: количество свободных мест на трапе
	err = operation(id, 2, ladder);
	if (err == -1)
	{
		perror("init2 error");
		return errno;
	}
//3: поездка: поездка началась - 0, нет - 1
	err = operation(id, 3, 1);
	if (err == -1)
	{
		perror("init3 error");
		return errno;
	}
///////////////////////////////////////////////////////////////////////////////////////////////////

	cap = fork(); //процесс капитан
	if(cap == 0)
	{
		c = capitan(id, travels);
		if (c != 0)
		{
			perror("capitan error");
			return errno;
		}
		exit(0);
	}

	for(i = 0; i < tourists; i++) //процессы туристы
	{
		tour = fork();
		if(tour == 0)
		{
			t = tourist(id, i);
			if(t != 0)
			{
				perror("tourist error");
				return errno;
			}
			exit(0);
		}
	}

	

	while(wait(&w) != -1)
	{
		//w = wait(&w);
	}


	/*for(i = 0; i < nsem; i++)
	{
		int cls = semctl(id,IPC_RMID,i);
			if(cls == -1)
			{	
				perror("ctl error");
				return errno;
			}
	}*/

	return 0;
}
