#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

void copy(char *from, char *to, int f, int i, int v)
{
	
	int opfr = 42,opto = 42,rfr = 42,wto = 42,cfr = 42, cto = 42;
	char buf[4096];

	opfr = open(from, O_RDONLY, 077);
	if (opfr == -1)
	{	
		perror("open from failed\n");
		return;	
	}

	opto = open(to, O_WRONLY | O_CREAT, 077);
	if (opto == -1)
	{
		if (f == 0){
			perror("open to failed\n");
			return;
		}
		int r = remove (to);
		if (r == -1){
			perror("remove failed\n");
			return;
		}
		opto = open(to, O_WRONLY | O_CREAT, 077);
	}

	rfr = read(opfr, buf, 4096);
	if (rfr < 0)
	{
		perror("read failed\n");
		return;
	}

	wto = write(opto, buf, rfr);
	if (wto < 0)
	{
		perror("write failed\n");
		return;
	}

	cfr = close(opfr);
	if (cfr < 0)
	{
		perror("write failed\n");
		return;
	}

	cto = close(opto);
	if (cto < 0)
	{
		perror("write failed\n");
		return;
	}

}


int main(int ac, char *av[])
{
	int go = 0, f=0, i=0, v=0, question = 0;

	while (go != -1)
	{
		go = getopt(ac, av, "fiv");
		switch (go)
		{
			case '?':
				printf("invalid option name");
				return 0;
			case 'f':
				f++;
				break;
			case 'i':
				i++;
				break;
			case 'v':
				v++;
				break;
		}
	}

	/*go = 0;

	while (go != -1)
	{
		go = getopt_long(ac, av, "fiv", long_options, &option_index);
		switch (go)
		{
			case '?':
				printf("invalid option name");
				return 0;
			case 'f':
				f++;
				break;
			case 'i':
				i++;
				break;
			case 'v':
				v++;
				break;
		}
	}*/

	char buf1[128];

	if(i == 0)
		copy(av[ac - 2], av[ac - 1], f, i, v);
	else
	{
		write(1, "mycp: overwrite", strlen("mycp: overwrite"));
		write(1, av[ac - 1], sizeof(av[ac - 1]));
		write(1, "? ", strlen("? "));
		int rd = read(0, buf1, 128);
		if ((buf1[0] != 'y') && (buf1[0] != 'Y'))
		{
			copy(av[ac - 2], av[ac - 1], f, i, v);
			question++;
		}
	}

	copy(av[ac - 2], av[ac - 1], f, i, v);


	if ((v != 0) && (question == 0))
		printf("'%s' -> '%s'\n", av[ac - 2], av[ac - 1]);
	
	return 0;
}
