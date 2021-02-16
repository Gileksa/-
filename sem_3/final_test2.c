/*вместо флага O_NONBLOCK  использовать poll*/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include <poll.h>

int main(int ac, char *av[])
{
	int pipefd[2],p,counter = 0,wr;
	char s = 'x';
	
//нужно сделать pipe
	p = pipe(pipefd);
	if (p == -1)
	{
		perror("pipe error");
		return errno;
	}

	struct pollfd str;
	str.fd = pipefd[1];
	str.events = POLLOUT;//не блокируется

	while(poll(&str, 1, 100))
	{
		write(pipefd[1],&s,1);
		counter++;
	}	
	printf("Buffer size is %d\n", counter);

	return 0;
}
