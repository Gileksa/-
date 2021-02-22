#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main()
{
	write(1, "Hello, world\n", strlen("Hello, world\n"));
	return 0;
}
