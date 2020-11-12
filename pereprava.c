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

struct mes
{
	long type;
	int mtext;
};

int min(int x, int y)
{
	if(x < y)
		return x;
	return y;
}

int parom(int id, int N, int ns, int nn)
{
	int M1 = 0, M2 = 0, i = 0, froms = 0, fromn = 0, mes1, mes2, mes3, mes4, mes5, mes6, mes7, mes8;
	struct mes carcameins, carcameouts, carcameinn, carcameoutn;

	while ((ns+nn) != 0) //пока на каком-то берегу еще есть машины
	{	
		printf("The ferry is on south\n");//выгружаем что привезли с севера

		for(i = fromn; i < fromn + M2; i++)
		{
			struct mes comeoutn = {7,i};
			mes7 = msgsnd(id, &comeoutn, sizeof(struct mes), 0);//пригласили машину выезжать
			if(mes7 == -1)
			{
				perror("parmes7 error");
				return errno;
			}
			mes8 = msgrcv(id, &carcameoutn, sizeof(struct mes), 8, 0);//подождали пока выедет, только потом зовем следующую
			if(mes8 == -1)
			{
				perror("parmes8 error");
				return errno;
			}
		}
		nn = nn - M2;//M2 машин с севера уехали. Совсем

		if (nn + ns == 0)//есть ли смысл куда-то ехать?
			return 0;
		
		fromn =+ M2;

		M1 = min(N, ns);
		//надо загрузить
		for(i = froms; i < froms + M1; i++)
		{
			struct mes comeins = {1,i};
			mes1 = msgsnd(id, &comeins, sizeof(struct mes), 0);//пригласили машину заезжать
			if(mes1 == -1)
			{
				perror("parmes1 error");
				return errno;
			}
			mes2 = msgrcv(id, &carcameins, sizeof(struct mes), 2, 0);//подождали, пока заедет
			if(mes2 == -1)
			{
				perror("parmes2 error");
				return errno;
			}
			//printf("%d is here\n", i);
		}
	
		if (nn + ns == 0)//надо ли куда-то ехать?
			return 0;
		
		//usleep(5); //это чтобы с принтфами нормально все было
		printf("The ferry is on north\n");//надо разгрузить
		for(i = froms; i < froms + M1; i++)
		{
			struct mes comeouts = {3,i};
			mes3 = msgsnd(id, &comeouts, sizeof(struct mes), 0);//пригласили машину выезжать
			if(mes3 == -1)
			{
				perror("parmes3 error");
				return errno;
			}
			mes4 = msgrcv(id, &carcameouts, sizeof(struct mes), 4, 0);//подождали пока выедет, только потом зовем следующую
			if(mes4 == -1)
			{
				perror("parmes4 error");
				return errno;
			}
		}
		
		ns=ns-M1;
		
		froms =+ M1;
		
		M2 = min(N, nn);
		if(M2 == 0)
			return 0;
		for(i = fromn; i < fromn + M2; i++)
		{
			struct mes comeinn = {5,i};
			mes5 = msgsnd(id, &comeinn, sizeof(struct mes), 0);//пригласили машину заезжать
			if(mes5 == -1)
			{
				perror("parmes5 error");
				return errno;
			}
			mes6 = msgrcv(id, &carcameinn, sizeof(struct mes), 6, 0);//подождали, пока заедет
			if(mes6 == -1)
			{
				perror("parmes6 error");
				return errno;
			}
		}
		
	}
	return 0;
}

int southcar(int id, int i)
{
	int mes1, mes2, mes3, mes4;
	struct mes cancomein, cancomeout; //получение приглашения

	mes1 = msgrcv(id, &cancomein, sizeof(struct mes), 1, 0);//получил приглашение
	if(mes1 == -1)
		{
			perror("scarmes1 error");
			return errno;
		}
	printf("%d go\n", i);

	struct mes camein = {2,i}; //подтверждение заезда
	mes2 = msgsnd(id, &camein, sizeof(struct mes), 0);//отчитался, что заехал
	if(mes2 == -1)
		{
			perror("scarmes2 error");
			return errno;
		}
	printf("%d is on the ferry\n", i);

	mes3 = msgrcv(id, &cancomeout, sizeof(struct mes), 3, 0);//получил приглашение выехать
	if(mes3 == -1)
		{
			perror("scarmes3 error");
			return errno;
		}
	printf("%d go out\n", i);

	struct mes cameout = {4,i}; //подтверждение выезда
	mes4 = msgsnd(id, &cameout, sizeof(struct mes), 0);//отчитался, что выехал
	if(mes4 == -1)
		{
			perror("scarmes4 error");
			return errno;
		}
	printf("%d is out of the ferry\n", i);
	return 0;
}

int northcar(int id, int i)
{
	int mes5, mes6, mes7, mes8;
	struct mes cancomeinn, cancomeoutn; //получение приглашения

	mes5 = msgrcv(id, &cancomeinn, sizeof(struct mes), 5, 0);//получил приглашение
	if(mes5 == -1)
		{
			perror("scarmes5 error");
			return errno;
		}
	printf("%d go\n", i);

	struct mes cameinn = {6,i}; //подтверждение заезда
	mes6 = msgsnd(id, &cameinn, sizeof(struct mes), 0);//отчитался, что заехал
	if(mes6 == -1)
		{
			perror("scarmes6 error");
			return errno;
		}
	printf("%d is on the ferry\n", i);
	
	mes7 = msgrcv(id, &cancomeoutn, sizeof(struct mes), 7, 0);//получил приглашение выехать
	if(mes7 == -1)
		{
			perror("scarmes7 error");
			return errno;
		}
	printf("%d go out\n", i);

	struct mes cameoutn = {8,i}; //подтверждение выезда
	mes8 = msgsnd(id, &cameoutn, sizeof(struct mes), 0);//отчитался, что выехал
	if(mes8 == -1)
		{
			perror("scarmes4 error");
			return errno;
		}
	printf("%d is out of the ferry\n", i);
	return 0;
};

int main(int ac, char *av[])
{	
	int N = atoi(av[1]); //количество мест на пароме
	int ns = atoi(av[2]); //количество машин на юге
	int nn = atoi(av[3]); //количество машин на севере
	int w = 42;
	
	setbuf(stdout, NULL); //не буферизуем вывод
	struct msqid_ds buf; //открыли очередь
	
	int id = msgget(IPC_PRIVATE, (IPC_CREAT | IPC_EXCL | 0700));
	if(id == -1)
	{
		perror("get error");
		return errno;
	}

//паром
	int p;
	int par = fork();
	if (par == 0)
	{
		p = parom(id, N, ns, nn);
		if(p != 0)
		{
			perror("parom error");
			return errno;
		}
		exit(0);
	}	

//машины на юге
	int i,car,c;
	for(i = 0; i < ns; i++)
	{
		car = fork();
		if(car == 0)
		{
			c = southcar(id, i);
			if(c != 0)
			{
				perror("southcar error");
				return errno;
			}
			exit(0);
		}
	}

//машины на севере
	for(i = ns; i < (nn + ns); i++)
	{
		car = fork();
		if(car == 0)
		{
			c = northcar(id, i);
			if(c != 0)
			{
				perror("northcar error");
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
