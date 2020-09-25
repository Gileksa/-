#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

void copy(int fd_src, int fd_dst)
{
	int n = 42,wn;
	char buf[4096];

	while(n != 0)
	{
		n = read(fd_src, buf, 4096);
		if (n < 0)
		{
			perror("read failed\n");
			break;
		}
		

		wn = write(fd_dst, buf, n);
		if (wn < 0)
		{
			perror("write failed\n");
			break;
		}
				
	}
}


void copyfile(const char *f_src, int f_dst)
{
	int n = 42,rn = 42,wn = 42,cn = 42;
	char buf[4096];

	n = open(f_src, O_RDONLY, 077);
	if (n == -1)
	{
		perror("open failed\n");
		return;
	}

	rn = read(n, buf, 4096);
	if (rn < 0)
	{
		perror("read failed\n");
		return;
	}

	wn = write(f_dst, buf, rn);
	if (wn < 0)
	{
		perror("write failed\n");
		return;
	}

	cn = close(n);
	if (cn < 0)
	{
		perror("write failed\n");
		return;
	}
}


int main(int ac, char *av[])
{
	int i;

	if (ac == 1){
		copy(0,1);
		return 0;
	}

	for(i = 1; i < ac; i++){
		copyfile(av[i], 1);
	}	
	return 0;
}
